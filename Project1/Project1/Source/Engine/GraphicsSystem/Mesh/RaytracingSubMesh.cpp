#include "RaytracingSubMesh.h"
#include "..//Shader/ShaderRecord.h"
#include "../..//Math/Matrix4x4.h"
#include "../HardwareBuffer/BottomLevelAccelerationStructure.h"
#include "../Enumerations/SubTopLevelAccelerationStructureFlags.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		RaytracingSubMesh::RaytracingSubMesh()
			: m_bottomLevelAS(nullptr)
			, m_sharedMaterial(nullptr)
			, m_matrix(Matrix4x4::Identity)
			, m_flags(SubTopLevelAccelerationStructureFlags::Opaque)
			, m_id(0)
			, m_mask(0xff)
			, m_dirty(true)
		{
		}

		RaytracingSubMesh::~RaytracingSubMesh()
		{
			for (auto& shaderRecord : m_shaderRecords)
			{
				delete shaderRecord;
			}
		}

		void RaytracingSubMesh::CreateShaderRecord(uint32_t recordCount)
		{
			m_shaderRecords.resize(recordCount);
			for (auto& shaderRecord : m_shaderRecords)
			{
				shaderRecord = new ShaderRecord();
			}
		}

		void RaytracingSubMesh::SetBottomLevelAS(BottomLevelASPtr bottomLevelAS)
		{
			m_bottomLevelAS = bottomLevelAS;
		}

		void RaytracingSubMesh::SetSharedMaterial(MaterialPtr material)
		{
			m_sharedMaterial = material;
		}

		void RaytracingSubMesh::SetFlags(SubTopLevelAccelerationStructureFlags flags)
		{
			m_flags = flags;
		}

		void RaytracingSubMesh::SetMask(uint32_t mask)
		{
			m_mask = mask;
		}

		void RaytracingSubMesh::SetTransformMatrix(const Matrix4x4& matrix)
		{
			m_matrix = matrix;
		}

		ShaderRecord* RaytracingSubMesh::GetShaderRecord(uint32_t index) const
		{
			return m_shaderRecords[index];
		}

		uint32_t RaytracingSubMesh::GetShaderRecordIndex(uint32_t index) const
		{
			return m_shaderRecords[index]->GetRegisterIndex();
		}

		SubTopLevelAccelerationStructureFlags RaytracingSubMesh::GetFlags() const
		{
			return m_flags;
		}

		uint32_t RaytracingSubMesh::GetID() const
		{
			return m_id;
		}

		uint32_t RaytracingSubMesh::GetMask() const
		{
			return m_mask;
		}

		const Matrix4x4& RaytracingSubMesh::GetTransformMatrix() const
		{
			return m_matrix;
		}

		void RaytracingSubMesh::SetName(const std::wstring& name)
		{

		}
	}
}