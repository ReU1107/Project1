#include "RaytracingTestPass.h"
#include "../Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

namespace
{
	// 最初のレイ生成シェーダー
	static const wchar_t* RayGenerateShader = L"RayGenerateShader";
	// ミスシェーダー
	static const wchar_t* MissShader = L"MissShader";
	// メッシュ処理シェーダー
	static const wchar_t* MeshShader = L"MeshShader";
	// メッシュ処理グループ
	static const wchar_t* MeshGroup = L"MeshGroup";

	// スカイドーム処理シェーダー
	static const wchar_t* SkyDomeShader = L"SkyDomeShader";
	// スカイドーム処理グループ
	static const wchar_t* SkyDomeGroup = L"SkyDomeGroup";
	// 球状衝突シェーダー
	static const wchar_t* SphereIntersectShader = L"SphereIntersectShader";

	// 反射処理シェーダー
	static const wchar_t* ReflectionShader = L"ReflectionShader";
	// 半透明処理シェーダー
	static const wchar_t* RefractionShader = L"RefractionShader";
	// 球型反射処理グループ
	static const wchar_t* SphereReflectionGroup = L"SphereReflectionGroup";
	// 球型半透明処理グループ
	static const wchar_t* SphereRefractionGroup = L"SphereRefractionGroup";

	static const wchar_t* AlphaCheckShader = L"AlphaCheckShader";

	// 影がつくか否かのチェック用シェーダー
	static const wchar_t* ShadowHitShader = L"ShadowHitShader";
	static const wchar_t* ShadowMissShader = L"ShadowMissShader";
	// シャドウ処理グループ
	static const wchar_t* ShadowMeshGroup = L"ShadowMeshGroup";
	static const wchar_t* ShadowSphereGroup = L"ShadowSphereGroup";
}

RaytracingTestPass::RaytracingTestPass()
{
}

RaytracingTestPass::~RaytracingTestPass()
{
}

void RaytracingTestPass::OnInitialize()
{
	//ComputePass::Register(L"RaytracingTestPass", this);

	//m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(100);

	//RootSignature* meshRootSignature = new RootSignature();
	//meshRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	//meshRootSignature->SetType(RootSignatureType::Local);
	//meshRootSignature->AddConstantBufferView(1);
	//meshRootSignature->AddShaderResourceView(1);
	//meshRootSignature->AddShaderResourceView(2);
	//meshRootSignature->AddShaderResourceView(3);
	//meshRootSignature->AddRange(1);
	//meshRootSignature->AddShaderResourceViewInRanges(4, 0);
	//meshRootSignature->AddStaticSamplerState();
	//meshRootSignature->Create();

	//RootSignature* sphereRootSignature = new RootSignature();
	//sphereRootSignature->AddShaderResourceView(0, 1);
	//sphereRootSignature->AddConstantBufferView(1);
	//sphereRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	//sphereRootSignature->SetType(RootSignatureType::Local);
	//sphereRootSignature->Create();

	//RootSignature* emptyRootSignature = new RootSignature();
	//emptyRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	//emptyRootSignature->SetType(RootSignatureType::Local);
	//emptyRootSignature->Create();

	//RootSignature* globalRootSignature = new RootSignature();
	//globalRootSignature->AddRange(3);
	//globalRootSignature->AddShaderResourceViewInRanges(0, 0);
	//globalRootSignature->AddUnorderedAccessViewInRanges(0, 0);
	//globalRootSignature->AddConstantBufferViewInRanges(0, 0);
	//globalRootSignature->Create();

	//ShaderCompiler compiler;
	//ShaderLibrary* shaderLibrary = compiler.CompileLibrary(L"Shader/RaytracingLib.hlsl", L"Shader/RaytracingStruct.hlsli");
	//const wchar_t* entryPoints[] = {
	//RayGenerateShader,MissShader,MeshShader , SkyDomeShader,
	//ReflectionShader,RefractionShader, SphereIntersectShader,ShadowHitShader,ShadowMissShader,AlphaCheckShader };

	//shaderLibrary->AddFunctionNames(entryPoints, nullptr, ARRAYSIZE(entryPoints));

	//m_pipeline = new RaytracingPipeline();
	//m_pipeline->AddShaderLibrary(shaderLibrary);

	//m_pipeline->AddHitGroup(MeshGroup, MeshShader, nullptr, AlphaCheckShader);

	//m_pipeline->AddHitGroup(SkyDomeGroup, SkyDomeShader, nullptr, AlphaCheckShader);

	//m_pipeline->AddHitGroup(SphereReflectionGroup, ReflectionShader, SphereIntersectShader);
	//m_pipeline->AddHitGroup(SphereRefractionGroup, RefractionShader, SphereIntersectShader);

	//m_pipeline->AddHitGroup(ShadowMeshGroup, ShadowHitShader);

	//m_pipeline->AddHitGroup(ShadowSphereGroup, ShadowHitShader, SphereIntersectShader);

	//const wchar_t* ClosestHitShader[] = { MeshShader,SkyDomeShader ,AlphaCheckShader };
	//m_pipeline->AddLocalRootSignature(meshRootSignature, ClosestHitShader, ARRAYSIZE(ClosestHitShader));
	//const wchar_t* IntersectSphereGroup[] = { SphereIntersectShader,ReflectionShader,RefractionShader,ShadowHitShader };
	//m_pipeline->AddLocalRootSignature(sphereRootSignature, IntersectSphereGroup, ARRAYSIZE(IntersectSphereGroup));
	//const wchar_t* MissShaderes[] = { MissShader,ShadowMissShader,RayGenerateShader };
	//m_pipeline->AddLocalRootSignature(emptyRootSignature, MissShaderes, ARRAYSIZE(MissShaderes));

	//m_pipeline->SetShaderConfig(sizeof(float) * 7, sizeof(float) * 5);
	//m_pipeline->AddAssociation(entryPoints, ARRAYSIZE(entryPoints));

	//m_pipeline->SetRaytraceMaxCount(10);

	//m_pipeline->AddGlobalRootSignature(globalRootSignature);

	//m_pipeline->Create();
	//CreateShaderTable();

	//auto sceneView = ResourceView::Create(m_shaderResourceDescriptor->GetInterface(), (IResource*)m_interface, ResourceViewType::Raytracing);

	//m_resultTexture = RenderTexture::Create("レイトレ用", 1280, 960, ResourceFormat::RGBAUnorm, true);
	//m_resultTexture->CreateShaderResourceView(m_shaderResourceDescriptor);

	//ConstantBuffer* a = new ConstantBuffer();
	//a->CreateBuffer();

	//SceneData sceneData = {};
	//sceneData.lightColor = Ambient;
	//sceneData.refraction = 1.0f;

	//s_sceneBuffer = new ConstantBuffer();
	//s_sceneBuffer->SetStride(sizeof(SceneData));
	//s_sceneBuffer->SetCount(1);
	//s_sceneBuffer->CreateBuffer(&sceneData);
	//s_sceneBuffer->SetName(L"シーン定数バッファ");

	//s_resultView = ResourceView::Create(s_descriptor, s_resultTexture->GetResource(), ResourceViewType::UnorderedAccess);

	//s_sceneBufferView = ResourceView::Create(s_descriptor, s_sceneBuffer, ResourceViewType::ConstantBuffer);

	//m_shaderResourceDescriptor;

	//auto objects = m_belongScene->GetObjects();

	//for (auto& object : objects)
	//{
	//	auto tracer = object->GetComponent<RayTracer>();
	//	if (tracer)
	//	{
	//		auto mesh = tracer->GetMesh();
	//		for (const auto& shaderName : tracer->GetShaderNames())
	//		{
	//			auto identifier = m_pipeline->GetShaderIdentifier(shaderName.c_str());
	//			mesh->AddShader(identifier);
	//		}
	//		mesh->SetShader(GetHitGroupTable());
	//		AddMesh(mesh);
	//	}
	//}
	//void* rayGenerate = m_pipeline->GetShaderIdentifier(RayGenerateShader);
	//void* miss = m_pipeline->GetShaderIdentifier(MissShader);
	//void* shadowMiss = m_pipeline->GetShaderIdentifier(ShadowMissShader);

	//RegisterRayGenerateRecord(rayGenerate);
	//RegisterMissRecord(miss);
	//RegisterMissRecord(shadowMiss);

}

void RaytracingTestPass::OnDispatch()
{
	if (!m_active)
		return;

	Start();
	auto list = CommandList::Find<ComputeCommandList>("Compute");
	auto queue = CommandQueue::Find<ComputeCommandQueue>("Compute");

	// 変更があったら読んでください

	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	list->SetComputeRootSignature(m_globalRootSignature);

	list->SetComputeDescriptorTable(m_shaderResourceDescriptor, 0);

	// レイトレーシング実行
	list->DispatchRaytracing(ResolutionWidth, ResolutionHeight, 1, GetRayGenerateTable(), GetHitGroupTable(), GetMissTable(), nullptr);

	Resource* resource = m_resultTexture->GetResource();
	list->UnorderedAccessBarrier(&resource, 1);

	m_shaderResourceDescriptor->Reset();

	std::shared_ptr<ComputeCommandList> lists[] = { list };
	queue->ExecuteCommandLists(lists, 1);

	queue->WaitExecutionList();
	list->Reset();

	End();
}
