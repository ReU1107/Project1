#include "TerrainController.h"
#include "../CustomPass/RaytracingShadowPass.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

TerrainController::TerrainController() noexcept
	: base("TerrainController")
{
}

TerrainController::~TerrainController() noexcept
{
}

void TerrainController::OnStart()
{
	auto renderer = GetComponent<MeshRenderer>();
	auto mesh = renderer->GetMesh();

	auto rMesh = RaytracingMesh::Create(mesh, 2);
	auto tracer = AddComponent<RayTracer>();
	tracer->SetMesh(rMesh);
	tracer->AddHitGroupName(ShadowCheckGroup);
	tracer->AddHitGroupName(ShadowHitGroup);
}

void TerrainController::OnUpdate(float deltaTime)
{
}
