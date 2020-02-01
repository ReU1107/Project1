#include "RaytracingShadowPass.h"
#include "..//Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

RaytracingShadowPass::RaytracingShadowPass()
	: base()
{
}

RaytracingShadowPass::~RaytracingShadowPass()
{
}

void RaytracingShadowPass::OnInitialize()
{
	Register(L"RaytracingShadowPass", this);

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(200);
	m_shaderResourceDescriptor->SetName(L"デスクリプター");

	m_resultTexture = Texture::Create("レイトレシャドウ結果", ResolutionWidth, ResolutionHeight, ResourceFormat::RGBAUnorm, false, false, true);
	m_resultTexture->SetName(L"レイトレシャドウ結果テクスチャ");

	m_globalRootSignature = new RootSignature();
	m_globalRootSignature->AddRange(5);
	m_globalRootSignature->AddShaderResourceViewInRanges(0, 0);
	m_globalRootSignature->AddUnorderedAccessViewInRanges(0, 0);
	m_globalRootSignature->AddConstantBufferViewInRanges(0, 0);
	m_globalRootSignature->AddConstantBufferViewInRanges(1, 0);
	m_globalRootSignature->AddShaderResourceViewInRanges(1, 0);

	m_globalRootSignature->Create();

	m_localRootSignatures.resize(2);

	m_localRootSignatures[0] = new RootSignature();
	m_localRootSignatures[0]->SetFlags(RootSignatureFlags::LocalRootSignature);
	m_localRootSignatures[0]->SetType(RootSignatureType::Local);
	m_localRootSignatures[0]->AddShaderResourceView(0, 1);
	//m_localRootSignatures[0]->AddShaderResourceView(1, 1);
	m_localRootSignatures[0]->AddShaderResourceView(2, 1);
	//m_localRootSignatures[0]->AddRange(1);
	//m_localRootSignatures[0]->AddShaderResourceViewInRanges(3, 0, 1, 1);
	//m_localRootSignatures[0]->AddStaticSamplerState();
	m_localRootSignatures[0]->Create();

	m_localRootSignatures[1] = new RootSignature();
	m_localRootSignatures[1]->SetFlags(RootSignatureFlags::LocalRootSignature);
	m_localRootSignatures[1]->SetType(RootSignatureType::Local);
	m_localRootSignatures[1]->Create();

	ShaderCompiler compiler;
	ShaderLibrary* shaderLibrary = compiler.CompileLibrary(L"Shader/RaytracingShadowLib.hlsl", L"Shader/RaytracingStruct.hlsli");
	const wchar_t* entryPoints[] = {
	RayGenerateShader,MissShader,ShadowCheckShader , NoneShadowCheckShader,
	ShadowHitShader, ShadowMissShader };

	shaderLibrary->AddFunctionNames(entryPoints, nullptr, ARRAYSIZE(entryPoints));

	m_pipeline = new RaytracingPipeline();
	m_pipeline->AddShaderLibrary(shaderLibrary);

	m_pipeline->AddHitGroup(ShadowCheckGroup, ShadowCheckShader);
//	m_pipeline->AddHitGroup(ShadowAlphaCheckGroup, ShadowCheckShader, nullptr, AlphaCheckShader);

	m_pipeline->AddHitGroup(ShadowNoneCheckGroup, NoneShadowCheckShader);
//	m_pipeline->AddHitGroup(ShadowNoneAlphaCheckGroup, NoneShadowCheckShader, nullptr, AlphaCheckShader);

	m_pipeline->AddHitGroup(ShadowHitGroup, ShadowHitShader);

	const wchar_t* CheckShader[] = { ShadowCheckShader };
	m_pipeline->AddLocalRootSignature(m_localRootSignatures[0], CheckShader, ARRAYSIZE(CheckShader));

	const wchar_t* NotUseLocalSignature[] = { MissShader,ShadowMissShader,RayGenerateShader,ShadowHitShader,NoneShadowCheckShader };
	m_pipeline->AddLocalRootSignature(m_localRootSignatures[1], NotUseLocalSignature, ARRAYSIZE(NotUseLocalSignature));

	m_pipeline->SetShaderConfig(sizeof(float) * 7, sizeof(float) * 5);
	m_pipeline->AddAssociation(entryPoints, ARRAYSIZE(entryPoints));

	m_pipeline->SetRaytraceMaxCount(10);

	m_pipeline->AddGlobalRootSignature(m_globalRootSignature);

	m_pipeline->Create();

	CreateShaderTable();

	auto objects = m_belongScene->GetObjects();
	uint32_t subMeshCount = 0;
	for (auto& tracer : RayTracer::allRayTracers)
	{

		auto mesh = tracer->GetMesh();
		subMeshCount += mesh->GetSubMeshCount();
		for (const auto& hitGroupName : tracer->GetHitGroupNames())
		{
			auto identifier = m_pipeline->GetShaderIdentifier(hitGroupName.c_str());
			mesh->AddShader(identifier);
		}
		mesh->SetShader(GetHitGroupTable());
		m_active = true;
	}
	m_subDescs.resize(subMeshCount);

	void* rayGenerate = m_pipeline->GetShaderIdentifier(RayGenerateShader);
	void* miss = m_pipeline->GetShaderIdentifier(MissShader);
	void* shadowMiss = m_pipeline->GetShaderIdentifier(ShadowMissShader);

	RegisterRayGenerateRecord(rayGenerate);
	RegisterMissRecord(miss);
	RegisterMissRecord(shadowMiss);
	if (m_active)
	{
		GetRayGenerateTable()->Create();
		GetMissTable()->Create();
		GetHitGroupTable()->Create();
	}

}

void RaytracingShadowPass::OnDispatch()
{
	if (!m_active)
		return;

	Start();
	DBGSTR(" ====== A2 \n");

	auto lightBuffer = m_belongScene->GetLightBuffer();
	auto sceneBuffer = m_belongScene->GetSceneBuffer();

	auto cameraBuffer = Camera::current->GetConstantBuffer();
	
	auto list = CommandList::Find<GraphicsCommandList>("Graphics2");
	auto queue = CommandQueue::Find<GraphicsCommandQueue>("Graphics2");

	// ライトの情報を更新する
	Buffer* buffer = { lightBuffer };
	list->ResourceBarrier(&buffer, 1, ResourceStates::CopyDestination);

	list->CopyBuffer(lightBuffer);

	list->ResourceBarrier(&buffer, 1, ResourceStates::GenericRead);

	auto objects = m_belongScene->GetObjects();

	TopLevelAccelerationStructureDesc desc = {};
	uint32_t count = 0;

	for (auto& tracer : RayTracer::allRayTracers)
	{
		if (!tracer->IsView())
			continue;
		if (!tracer->CastingShadow())
			continue;

		auto mesh = tracer->GetMesh();
		Matrix4x4 matrix = tracer->GetTransform()->GetLocalToWorld();
		uint32_t subMeshCount = mesh->GetSubMeshCount();
		auto& subMeshes = mesh->GetSubMeshes();

		for (uint32_t i = 0; i < subMeshCount; ++i)
		{
			auto& subMesh = subMeshes[i];
			auto& subDesc = m_subDescs[count++];

			auto bottomLevelAS = subMesh->GetBottomLevelAS();
			for (auto vertexBuffer : bottomLevelAS->GetVertexBuffers())
			{
				Buffer* v = vertexBuffer;
				if (!v->GetCopyable())
					break;
				//list->ResourceBarrier(&v, 1, ResourceStates::CopyDestination);

				//list->CopyBuffer(vertexBuffer);

				//list->ResourceBarrier(&v, 1, ResourceStates::GenericRead);

			}
			if (tracer->IsReBuild())
			{
				bottomLevelAS->Dirty(true);
			}

			list->BuildBottomLevelAS(bottomLevelAS);

			subDesc.bottom = bottomLevelAS->GetInterface();
			subDesc.contribution = subMesh->GetShaderRecordIndex();
			subDesc.flags = subMesh->GetFlags();
			subDesc.id = subMesh->GetID();
			subDesc.mask = subMesh->GetMask();
			subDesc.matrix = matrix;
		}
	}

	m_topLevelAS->Recreate(count);

	// 変更があったら読んでください
	desc.descs = m_subDescs.data();
	desc.bottomCount = m_subDescs.size();
	m_topLevelAS->Update(desc);

	m_shaderResourceDescriptor->Reset();

	m_topLevelAS->RecreateResourceView(m_shaderResourceDescriptor);

	m_resultTexture->RecreateUnorderedAccessView(m_shaderResourceDescriptor);

	sceneBuffer->RecreateResourceView(m_shaderResourceDescriptor);

	cameraBuffer->RecreateResourceView(m_shaderResourceDescriptor);

	lightBuffer->RecreateResourceView(m_shaderResourceDescriptor);

	Resource* resources[] = { m_resultTexture->GetResource() };
	list->ResourceBarrier(resources, 1, ResourceStates::UnorderedAccess);

	list->BuildTopLevelAS(m_topLevelAS);

	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	list->SetComputeRootSignature(m_globalRootSignature);

	list->SetComputeDescriptorTable(m_shaderResourceDescriptor, 0);

	list->SetRaytracingPipeline(m_pipeline);

	// レイトレーシング実行
	list->DispatchRaytracing(ResolutionWidth, ResolutionHeight, 1, GetRayGenerateTable(), GetHitGroupTable(), GetMissTable(), nullptr);

	Resource* resource = m_resultTexture->GetResource();
	list->UnorderedAccessBarrier(&resource, 1);

	list->ResourceBarrier(resources, 1, ResourceStates::GenericRead);

	m_shaderResourceDescriptor->Reset();
	DBGSTR(" ====== B2 \n");

	std::shared_ptr<GraphicsCommandList> lists[] = { list };
	queue->ExecuteCommandLists(lists, 1);

	queue->WaitExecutionList();
	list->Reset();

	DBGSTR(" ====== C2 \n");

	End();

}
