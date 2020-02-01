#include "SubMesh.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		SubMesh::SubMesh(const std::string& name)
			: m_name(name)
			, m_material(nullptr)
			, m_indexBuffer(nullptr)
			, m_startIndexLocation(0)
			, m_useIndexCount(0)
		{
		}

		SubMesh::~SubMesh()
		{
			delete m_indexBuffer;
		}

		void SubMesh::SetMaterial(MaterialPtr material)
		{
			m_material = material;
		}

		void SubMesh::SetIndexBuffer(IndexBuffer* indexBuffer)
		{
			m_indexBuffer = indexBuffer;
		}

		void SubMesh::SetStartIndexLocation(uint32_t startLocation)
		{
			m_startIndexLocation = startLocation;
		}

		void SubMesh::SetUseIndexCount(uint32_t indexCount)
		{
			m_useIndexCount = indexCount;
		}

		SubMesh::MaterialPtr SubMesh::GetMaterial() const
		{
			return m_material;
		}

		IndexBuffer* SubMesh::GetIndexBuffer() const
		{
			return m_indexBuffer;
		}

		uint32_t SubMesh::GetStartIndexLocation() const
		{
			return m_startIndexLocation;
		}

		uint32_t SubMesh::GetUseIndexCount() const
		{
			return m_useIndexCount;
		}
	}
}