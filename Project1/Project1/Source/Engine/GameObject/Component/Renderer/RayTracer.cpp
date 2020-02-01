#include "RayTracer.h"
#include "../../../GraphicsSystem/Mesh/RaytracingMesh.h"
#include "../../../GraphicsSystem/Mesh/RaytracingSubMesh.h"
#include "../Transform.h"

namespace Engine
{

	std::vector<RayTracer::RayTracerPtr> RayTracer::allRayTracers;

	RayTracer::RayTracer() noexcept
		: base("RayTracer")
		, m_mesh(nullptr)
		, m_hitGroupNames()
		, m_isRebuild(false)
	{
	}

	RayTracer::~RayTracer() noexcept
	{
	}
	
	void RayTracer::AddHitGroupName(const std::wstring& name)
	{
		m_hitGroupNames.push_back(name);
	}

	void RayTracer::SetMesh(RaytracingMeshPtr mesh)
	{
		m_mesh = mesh;
	}

	RayTracer::RaytracingMeshPtr RayTracer::GetMesh() const
	{
		auto worldMatrix = GetTransform()->GetLocalToWorld();

		for (auto& subMesh : m_mesh->GetSubMeshes())
		{
			subMesh->SetTransformMatrix(worldMatrix);
		}

		return m_mesh;
	}

	const RayTracer::HitGroupNames& RayTracer::GetHitGroupNames() const
	{
		return m_hitGroupNames;
	}
}