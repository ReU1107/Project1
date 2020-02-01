#include "ProceduralMesh.h"
#include "..//HardwareBuffer//StructuredBuffer.h"
#include "Material.h"
#include "SubMesh.h"

namespace Engine
{
	namespace GraphicsSystem
	{

		ProceduralMesh::ProceduralMesh()
			: m_buffer(nullptr)
		{
		}

		ProceduralMesh::~ProceduralMesh()
		{
			delete m_buffer;
			uint32_t subMeshCount = (uint32_t)m_subMeshes.size();

			for (uint32_t i = 0; i < subMeshCount; ++i)
			{
				auto& subMesh = m_subMeshes[i];
				delete subMesh;
			}
		}

		void ProceduralMesh::AddAABB(const DirectX::XMFLOAT3& min, const DirectX::XMFLOAT3& max)
		{
			AxisAlignedBoundingBox aabb = {};
			aabb.minX = min.x;
			aabb.minY = min.y;
			aabb.minZ = min.z;

			aabb.maxX = max.x;
			aabb.maxY = max.y;
			aabb.maxZ = max.z;

			m_aabbs.push_back(aabb);
		}

		void ProceduralMesh::AddSphere(const DirectX::XMFLOAT3& center, float radius)
		{
			AxisAlignedBoundingBox aabb = {};
			aabb.minX = center.x - radius;
			aabb.minY = center.y - radius;
			aabb.minZ = center.z - radius;

			aabb.maxX = center.x + radius;
			aabb.maxY = center.y + radius;
			aabb.maxZ = center.z + radius;

			m_aabbs.push_back(aabb);
		}

		void ProceduralMesh::AddSubMesh(SubMesh* subMesh)
		{
			m_subMeshes.push_back(subMesh);
		}

		ProceduralMesh::SubMeshes& ProceduralMesh::GetSubMeshes()
		{
			return m_subMeshes;
		}

		void ProceduralMesh::Create()
		{
			m_buffer = new StructuredBuffer();

			m_buffer->SetCount(m_aabbs.size());
			m_buffer->SetStride(sizeof(AxisAlignedBoundingBox));

			m_buffer->Create(m_aabbs.data());
			uint32_t subMeshCount = (uint32_t)m_subMeshes.size();

			for (uint32_t i = 0; i < subMeshCount; ++i)
			{
				auto& subMesh = m_subMeshes[i];
				auto material = subMesh->GetMaterial();
				material->CreateConstantBuffer();

			}

		}

		StructuredBuffer* ProceduralMesh::GetBuffer() const
		{
			return m_buffer;
		}
	}
}