#include "Test2.h"

#include "PMX/PMXLoader.h"
#include "Resolution.h"

#include "Engine/Include.h"

// この二つは抽象化が完了しだい消します
#include "Engine/GraphicsSystem/Interface/IRaytracingPipeline.h"
#include "Engine/GraphicsSystem/Interface/IRootSignature.h"
#include "Engine/GraphicsSystem/Interface/IResource.h"

#include <random>
/*
DirectX Intermediate Language
		中間	　　 言語
DXIL
*/
struct SceneData
{
	DirectX::XMFLOAT4X4 projToWorld;		// 
	DirectX::XMFLOAT4 cameraPosition;			// 
	DirectX::XMFLOAT3 lightPosition;			// 
	float refraction;
	DirectX::XMFLOAT3 lightColor;		// 
};
using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace DirectX;

static ResourceDescriptor* s_descriptor = nullptr;

static Texture* s_resultTexture = nullptr;

static ResourceView* s_resultView = nullptr;

static ResourceView* s_sceneView = nullptr;

static RaytracingScene* s_scene = nullptr;

static Mesh* s_dome = nullptr;

static Mesh* s_stage = nullptr;

static const uint32_t modelCount = 1;
static Mesh* s_mesh[modelCount] = {};
static RaytracingMesh* s_meshObject[modelCount] = {};

static RaytracingMesh* s_stageObject = nullptr;

static RaytracingMesh* s_domeObject = nullptr;

static const uint32_t sphereCount = 6;
static RaytracingMesh* s_sphereObject[sphereCount] = {};

static ConstantBuffer* s_sceneBuffer = nullptr;

static Texture* s_backGround = nullptr;

static RasterizerPipeline* rasterizerPipeline = nullptr;

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

static const Engine::Vector3 Ambient = Engine::Vector3(0.3f, 0.3f, 0.3f);

// 屈折率
static float Refraction[sphereCount] = { 1.000f,1.309f,1.3334f,1.5443f,2.417f ,1.0f };
// 屈折処理か、反射処理か
static bool SphereRefractionFunction[sphereCount] = { true,true,true,true,true,false };

void CreateMesh()
{
	PMXLoader loader;

	s_mesh[0] = loader.Load("Assets/木曽あずき/KisoAzuki.pmx");
	//s_mesh[0] = loader.Load("Assets/AliceX034X5MK5/アリスV034_X5MK5.pmx");

	//s_mesh[1] = loader.Load("Assets/夜桜たま/YozakuraTama.pmx");
	//s_mesh[2] = loader.Load("Assets/八重沢なとり/YaezawaNatori.pmx");
	//s_mesh[3] = loader.Load("Assets/花京院ちえり/KakyoinChieri.pmx");
	//s_mesh[4] = loader.Load("Assets/北上双葉/KitakamiFutaba.pmx");

	s_dome = loader.Load("Assets/スカイドーム_水底R1_配布物/Skydome_R1/Dome_R102.pmx");

	//s_stage = loader.Load("Assets/oldwood/軽量版/oldwood_lw.pmx");
	//s_stage = loader.Load("Assets/清水風/清水風固定影なし.pmx");
	//s_stage = loader.Load("Assets/廃教会/廃教会.pmx");
	s_stage = loader.Load("Assets/ガーデンステージ/青バラ/ガーデン青.pmx");

	// この関数内のここから下の処理は考え中
	/*
	下の処理が存在する理由としては
	テクスチャをVRAM上にコピーするのを待っておかないといけないため
	これがないと止まります というか止まった
	*/
	auto device = GetD3D12Device();

	device->ExecuteThisList();
	device->WaitExecutionThisList();

	auto list = GraphicsCommandList::Find(L"Default");

	for (uint32_t i = 0; i < modelCount; i++)
	{
		s_meshObject[i] = RaytracingMesh::Create(s_mesh[i], 2);
		s_meshObject[i]->Build(list);
	}

	s_stageObject = RaytracingMesh::Create(s_stage, 2);
	s_stageObject->SetFlags(RaytracingInstanceFlags::NonOpaque);
	s_stageObject->Build(list);

	s_domeObject = RaytracingMesh::Create(s_dome, 2);
	s_domeObject->SetFlags(RaytracingInstanceFlags::NonOpaque);
	s_domeObject->SetMask(0b00000001);
	s_domeObject->Build(list);

	std::random_device randomDevice;
	std::mt19937_64 mt(randomDevice());
	std::uniform_real_distribution<float> random200Ne(-100.0f, 100.0f);
	std::uniform_real_distribution<float> random200Na(0.0f, 200.0f);
	std::uniform_real_distribution<float> random10(10.0f, 20.0f);
	std::uniform_real_distribution<float> random1(0.0f, 1.0f);
	std::uniform_real_distribution<float> random2(0.0f, 2.0f);
	for (uint32_t i = 0; i < sphereCount; ++i)
	{
		ProceduralMesh* proc = new ProceduralMesh();
		proc->AddSphere(DirectX::XMFLOAT3(0, 0, 0), 10.0f);

		Material* material = new Material();
		material->SetColor(Color3(0.0f, 0.0f, 0.0f));
		material->SetOpacity(0.01f);
		material->SetRefraction(Refraction[i]);
		material->SetDiffuseCoeff(random1(mt));
		material->SetSpecularCoeff(random1(mt));
		material->SetSpecularity(random1(mt));
		SubMesh* sub = new SubMesh();
		sub->SetMaterial(material);
		proc->AddSubMesh(sub);

		proc->Create();

		s_sphereObject[i] = RaytracingMesh::Create(proc, 2);
		DirectX::XMFLOAT4X4 m = Matrix4x4::Identity;
		m._14 = -40.0f + (20.0f * i);
		m._24 = 10.0f;
		if (i == 5)
		{
			m._14 = 0.0f;
			m._34 = -30.0f;
		}
		else
		{
			m._34 = -150.0f;
		}
		s_sphereObject[i]->SetTransformMatrix(m);
		s_sphereObject[i]->Build(list);

	}

	DirectX::XMFLOAT4X4 m = Matrix4x4::Identity;

	for (uint32_t i = 0; i < modelCount; i++)
	{
		m._34 = i * -20.0f;// +10;
		s_meshObject[i]->SetTransformMatrix(m);
	}
	
	//s_sphereObject->SetTransformMatrix(t.GetLocalToWorld());

}

void CreateRaytracingScene()
{
	// シーン構築
	s_scene = new RaytracingScene();
	// レイトレーシングで処理を行うオブジェクトを登録する
	for (uint32_t i = 0; i < modelCount; i++)
	{
		s_scene->AddMesh(s_meshObject[i]);
	}
	s_scene->AddMesh(s_stageObject);
	s_scene->AddMesh(s_domeObject);
	for (uint32_t i = 0; i < sphereCount; ++i)
	{
		s_scene->AddMesh(s_sphereObject[i]);
	}

	s_scene->Create();
	s_scene->SetResultData(ResolutionWidth, ResolutionHeight, 1);
	s_scene->CreateShaderTable();
	s_scene->SetName(L"レイトレーシングシーン");

}
RootSignature* s_meshRootSignature = nullptr;
RootSignature* s_sphereRootSignature = nullptr;
RootSignature* s_emptyRootSignature = nullptr;
RootSignature * s_globalRootSignature = nullptr;
RaytracingPipeline * s_pipeline = nullptr;

void CreatePipeline()
{
	s_meshRootSignature = new RootSignature();
	s_meshRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	s_meshRootSignature->SetType(RootSignatureType::Local);
	s_meshRootSignature->AddConstantBufferView(1);
	s_meshRootSignature->AddShaderResourceView(1);
	s_meshRootSignature->AddShaderResourceView(2);
	s_meshRootSignature->AddShaderResourceView(3);
	s_meshRootSignature->AddRange(1);
	s_meshRootSignature->AddShaderResourceViewInRanges(4, 0);
	s_meshRootSignature->AddStaticSamplerState();
	s_meshRootSignature->Create();

	s_sphereRootSignature = new RootSignature();
	s_sphereRootSignature->AddShaderResourceView(0, 1);
	s_sphereRootSignature->AddConstantBufferView(1);
	s_sphereRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	s_sphereRootSignature->SetType(RootSignatureType::Local);
	s_sphereRootSignature->Create();

	s_emptyRootSignature = new RootSignature();
	s_emptyRootSignature->SetFlags(RootSignatureFlags::LocalRootSignature);
	s_emptyRootSignature->SetType(RootSignatureType::Local);
	s_emptyRootSignature->Create();

	s_globalRootSignature = new RootSignature();
	s_globalRootSignature->AddRange(3);
	s_globalRootSignature->AddShaderResourceViewInRanges(0, 0);
	s_globalRootSignature->AddUnorderedAccessViewInRanges(0, 0);
	s_globalRootSignature->AddConstantBufferViewInRanges(0, 0);
	s_globalRootSignature->Create();

	ShaderCompiler compiler;
	ShaderLibrary* shaderLibrary = compiler.CompileLibrary(L"Shader/RaytracingLib.hlsl", L"Shader/RaytracingStruct.hlsli");
	const wchar_t* entryPoints[] = {
	RayGenerateShader,MissShader,MeshShader , SkyDomeShader,
	ReflectionShader,RefractionShader, SphereIntersectShader,ShadowHitShader,ShadowMissShader,AlphaCheckShader };

	shaderLibrary->AddFunctionNames(entryPoints, nullptr, ARRAYSIZE(entryPoints));

	s_pipeline = new RaytracingPipeline();
	s_pipeline->AddShaderLibrary(shaderLibrary);

	s_pipeline->AddHitGroup(MeshGroup, MeshShader, nullptr, AlphaCheckShader);

	s_pipeline->AddHitGroup(SkyDomeGroup, SkyDomeShader, nullptr, AlphaCheckShader);

	s_pipeline->AddHitGroup(SphereReflectionGroup, ReflectionShader, SphereIntersectShader);
	s_pipeline->AddHitGroup(SphereRefractionGroup, RefractionShader, SphereIntersectShader);

	s_pipeline->AddHitGroup(ShadowMeshGroup, ShadowHitShader);
	
	s_pipeline->AddHitGroup(ShadowSphereGroup, ShadowHitShader, SphereIntersectShader);
	
	const wchar_t* ClosestHitShader[] = { MeshShader,SkyDomeShader ,AlphaCheckShader };
	s_pipeline->AddLocalRootSignature(s_meshRootSignature, ClosestHitShader, ARRAYSIZE(ClosestHitShader));
	const wchar_t* IntersectSphereGroup[] = { SphereIntersectShader,ReflectionShader,RefractionShader,ShadowHitShader };
	s_pipeline->AddLocalRootSignature(s_sphereRootSignature, IntersectSphereGroup, ARRAYSIZE(IntersectSphereGroup));
	const wchar_t* MissShaderes[] = { MissShader,ShadowMissShader,RayGenerateShader };
	s_pipeline->AddLocalRootSignature(s_emptyRootSignature, MissShaderes, ARRAYSIZE(MissShaderes));

	s_pipeline->SetShaderConfig(sizeof(float) * 7, sizeof(float) * 5);
	s_pipeline->AddAssociation(entryPoints, ARRAYSIZE(entryPoints));

	s_pipeline->SetRaytraceMaxCount(10);

	s_pipeline->AddGlobalRootSignature(s_globalRootSignature);

	s_pipeline->Create();

}

static ResourceView* s_sceneBufferView = nullptr;

void CreateResource()
{
	s_descriptor = ResourceDescriptor::CreateShaderResource(200);
	s_descriptor->SetName(L"デスクリプター");

	s_resultTexture = Texture::Create(ResolutionWidth, ResolutionHeight, ResourceFormat::RGBAUnorm, false, false, true);
	s_resultTexture->SetName(L"結果受け取り用テクスチャ");

	SceneData sceneData = {};
	sceneData.lightColor = Ambient;
	sceneData.refraction = 1.0f;

	s_sceneBuffer = new ConstantBuffer();
	s_sceneBuffer->SetStride(sizeof(SceneData));
	s_sceneBuffer->SetCount(1);
	s_sceneBuffer->CreateBuffer(&sceneData);
	s_sceneBuffer->SetName(L"シーン定数バッファ");

	s_sceneView = ResourceView::Create(s_descriptor->GetInterface(), (IResource*)s_scene->GetInterface(), ResourceViewType::Raytracing);

	s_resultView = ResourceView::Create(s_descriptor, s_resultTexture->GetResource(), ResourceViewType::UnorderedAccess);

	s_sceneBufferView = ResourceView::Create(s_descriptor, s_sceneBuffer, ResourceViewType::ConstantBuffer);
	// 設定できるデスクリプターテーブルが一つのため全ての情報が入ったデスクリプターにコピーする
	for (auto& subMesh : s_stage->GetSubMeshes())
	{
		auto material = subMesh->GetMaterial();
		if (!material->GetDecalTexture())
			continue;
		s_descriptor->CopyView(material->GetDecalTexture()->GetShaderResourceView());
	}
	for (uint32_t i = 0; i < modelCount; i++)
	{
		for (auto& subMesh : s_mesh[i]->GetSubMeshes())
		{
			auto material = subMesh->GetMaterial();
			if (!material->GetDecalTexture())
				continue;
			s_descriptor->CopyView(material->GetDecalTexture()->GetShaderResourceView());
		}
	}

	for (auto& subMesh : s_dome->GetSubMeshes())
	{
		auto material = subMesh->GetMaterial();
		if (!material->GetDecalTexture())
			continue;
		s_descriptor->CopyView(material->GetDecalTexture()->GetShaderResourceView());
	}
}

void CreateShaderTable()
{
	void* rayGenerate = s_pipeline->GetShaderIdentifier(RayGenerateShader);
	void* miss = s_pipeline->GetShaderIdentifier(MissShader);
	void* shadowMiss = s_pipeline->GetShaderIdentifier(ShadowMissShader);
	void* meshGroup = s_pipeline->GetShaderIdentifier(MeshGroup);
	void* reflectoinGroup = s_pipeline->GetShaderIdentifier(SphereReflectionGroup);
	void* refractionGroup = s_pipeline->GetShaderIdentifier(SphereRefractionGroup);
	void* skyDomeGroup = s_pipeline->GetShaderIdentifier(SkyDomeGroup);
	void* shadowMeshGroup = s_pipeline->GetShaderIdentifier(ShadowMeshGroup);
	void* shadowSphereGroup = s_pipeline->GetShaderIdentifier(ShadowSphereGroup);

	ShaderRecord* s_rayGenerateRecord = new ShaderRecord();
	s_rayGenerateRecord->SetShaderIdentifier(rayGenerate);

	ShaderRecord* s_missRecord = new ShaderRecord();
	s_missRecord->SetShaderIdentifier(miss);
	ShaderRecord* s_shadowMissRecord = new ShaderRecord();
	s_shadowMissRecord->SetShaderIdentifier(shadowMiss);

	ShaderTable* rayGenerateTable = s_scene->GetRayGenerateTable();
	ShaderTable* hitGroupTable = s_scene->GetHitGroupTable();
	ShaderTable* missTable = s_scene->GetMissTable();

	rayGenerateTable->RegisterShaderRecord(s_rayGenerateRecord);
	missTable->RegisterShaderRecord(s_missRecord);
	missTable->RegisterShaderRecord(s_shadowMissRecord);

	// ヒットテーブルにそれぞれのヒットグループシェーダーを登録する
	for (uint32_t i = 0; i < modelCount; i++)
	{
		s_meshObject[i]->AddShader(meshGroup);
		s_meshObject[i]->AddShader(shadowMeshGroup);
		s_meshObject[i]->SetShader(hitGroupTable);
	}

	s_stageObject->AddShader(meshGroup);
	s_stageObject->AddShader(shadowMeshGroup);
	
	s_domeObject->AddShader(skyDomeGroup);
	s_domeObject->AddShader(shadowMeshGroup);

	s_stageObject->SetShader(hitGroupTable);
	s_domeObject->SetShader(hitGroupTable);

	for (uint32_t i = 0; i < sphereCount; ++i)
	{
		bool refraction = SphereRefractionFunction[i];
		if (refraction)
		{
			s_sphereObject[i]->AddShader(refractionGroup);
		}
		else
		{
			s_sphereObject[i]->AddShader(reflectoinGroup);
		}
	
		s_sphereObject[i]->AddShader(shadowSphereGroup);
		s_sphereObject[i]->SetShader(hitGroupTable);
	}

	rayGenerateTable->Create();
	hitGroupTable->Create();
	missTable->Create();

}

void Test2::Init(HWND hWnd)
{
	Engine::GraphicsSystem::Startup(hWnd, ResolutionWidth, ResolutionHeight);

	CreateMesh();

	CreatePipeline();

	CreateRaytracingScene();

	CreateResource();
	// シェーダーテーブル作成
	CreateShaderTable();

}

void Test2::Update(float deltaTime)
{	
	s_scene->Update();

	auto device = GetD3D12Device();

	device->ExecuteThisList();
	device->WaitExecutionThisList();
}

void Test2::Render()
{
	auto device = GetD3D12Device();

	// レイトレーシングに使用する全てのデスクリプターヒープを設定する
	IDescriptorHeap* descriptorHeaps[] = { s_descriptor->GetInterface() };
	device->SetDescriptorHeaps(descriptorHeaps);

	RenderTexture* backBuffer = GetCurrentBackBuffer();

	IResource* resources[] = { 
		s_resultTexture->GetResource()->GetInterface(),
		backBuffer->GetResource()->GetInterface()
	};
	device->ResourceBarrierTransition(resources, 1, ResourceStates::CopySource, ResourceStates::UnorderedAccess);
	// ルートシグネチャ設定
	device->SetComputeRootSignature(s_globalRootSignature->GetInterface());
	device->SetComputeDescriptorTable(s_descriptor->GetInterface(), 0);

	// レイトレーシングに使用するパイプライン設定
	device->SetRaytracingPipeline(s_pipeline->GetInterface());

	// レイトレ開始
	s_scene->DispatchRaytracing();

	// レイトレが終了するまで待機
	device->UnorderedAccessBarrier(resources, 1);

	device->ResourceBarrierTransition(resources, 1, ResourceStates::UnorderedAccess, ResourceStates::CopySource);

	device->ResourceBarrierTransition(&resources[1], 1, ResourceStates::Present, ResourceStates::CopyDestination);

	device->CopyResource(resources[0], resources[1]);

	device->ResourceBarrierTransition(&resources[1], 1, ResourceStates::CopyDestination, ResourceStates::Present);

	// 描画処理終了
	device->EndFrameRender();

	GraphicsSystem::Present();
}

void Test2::Fin()
{
	Engine::GraphicsSystem::Shutdown();

}
