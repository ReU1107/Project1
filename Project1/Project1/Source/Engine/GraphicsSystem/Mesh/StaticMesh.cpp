#include "StaticMesh.h"
#include "../../Utility/EnumOperator.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		StaticMesh::StaticMesh(const std::string& name)
			: base(name, MeshType::Static)
		{
		}

		StaticMesh::~StaticMesh()
		{
		}
		
		void StaticMesh::Update()
		{
		}

		void StaticMesh::CreateVertexBuffes()
		{
			if (m_vertexCountIsDirty)
			{
				if ((m_layout & VertexLayout::Positions) != 0)
				{
					CreateVertexBuffer(m_positions.size(), sizeof(Vector3), (void*)m_positions.data());
				}
				if ((m_layout & VertexLayout::Normals) != 0)
				{
					CreateVertexBuffer(m_normals.size(), sizeof(Vector3), (void*)m_normals.data());
				}
				if ((m_layout & VertexLayout::Tangents) != 0)
				{
					//CreateVertexBuffer(VertexAttribute::Positions, m_positions.size(), sizeof(Vector3), .data());
				}
				if ((m_layout & VertexLayout::Texcoords0) != 0)
				{
					CreateVertexBuffer(m_texcoords0.size() / 2, sizeof(Vector2), (void*)m_texcoords0.data());
				}
				m_vertexCountIsDirty = false;
			}
		}
	}
}