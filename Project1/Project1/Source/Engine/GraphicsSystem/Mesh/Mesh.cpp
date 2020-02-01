#include "Mesh.h"
#include "Material.h"
#include "SubMesh.h"

#include "..//HardwareBuffer//VertexBuffer.h"
#include "..//HardwareBuffer//IndexBuffer.h"
#include "..//HardwareBuffer//ConstantBuffer.h"

#include "..//HardwareBuffer//ResourceDescriptor.h"
#include "..//Enumerations/DescriptorHeapType.h"
#include "..//Texture/Texture.h"
#include "..//HardwareBuffer//Resource.h"
#include "..//HardwareBuffer//ResourceView.h"
#include "..//Enumerations/ResourceViewType.h"
#include "../../Utility/EnumOperator.h"
#include "../Enumerations/ResourceFlags.h"

namespace Engine 
{
	namespace GraphicsSystem 
	{
		Mesh::Mesh(const std::string& name, MeshType type)
			: base(name)
			, m_vertexBuffers()
			, m_vertexBufferCount(0)
			, m_textureCount(0)
			, m_layout()
			, m_type(type)
			, m_vertexCountIsDirty(true)
		{
			AddVertexLayout(VertexLayout::Positions);
			AddVertexLayout(VertexLayout::Normals);
			AddVertexLayout(VertexLayout::Texcoords0);
		}

		Mesh::~Mesh()
		{
			for (auto& vertexBuffer : m_vertexBuffers)
			{
				delete vertexBuffer;
			}
		}

		uint32_t Mesh::GetVertexCount() const
		{
			return m_positions.size();
		}

		uint32_t Mesh::GetVertexBufferCount() const
		{
			return m_vertexBuffers.size();
		}

		Mesh::VertexBuffers& Mesh::GetVertexBuffers()
		{
			return m_vertexBuffers;
		}

		VertexBuffer* Mesh::GetVertexBuffer(uint32_t index) const
		{
			if (index > m_vertexBuffers.size())
			{
				assert(!"頂点バッファの数を超えた値が渡されています");
			}
			return m_vertexBuffers[index];
		}

		VertexBuffer* Mesh::GetVertexBuffer(VertexLayout layout) const
		{
			uint32_t index = 0;
			if ((m_layout & VertexLayout::Positions) != 0)
			{
				if (layout == VertexLayout::Positions)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Normals) != 0)
			{
				if (layout == VertexLayout::Normals)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Tangents) != 0)
			{
				if (layout == VertexLayout::Tangents)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::BoneWeights) != 0)
			{
				if (layout == VertexLayout::BoneWeights)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::BasePositions) != 0)
			{
				if (layout == VertexLayout::BasePositions)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::DeltaPositions) != 0)
			{
				if (layout == VertexLayout::DeltaPositions)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::DeltaNormals) != 0)
			{
				if (layout == VertexLayout::DeltaNormals)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::DeltaTangents) != 0)
			{
				if (layout == VertexLayout::DeltaTangents)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Texcoords0) != 0)
			{
				if (layout == VertexLayout::Texcoords0)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Texcoords1) != 0)
			{
				if (layout == VertexLayout::Texcoords1)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Texcoords2) != 0)
			{
				if (layout == VertexLayout::Texcoords2)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}
			if ((m_layout & VertexLayout::Texcoords3) != 0)
			{
				if (layout == VertexLayout::Texcoords3)
				{
					return m_vertexBuffers[index];
				}
				index++;
			}

			return nullptr;
		}

		Mesh::Positions& Mesh::GetPositions()
		{
			return m_positions;
		}

		Mesh::Normals& Mesh::GetNormals()
		{
			return m_normals;
		}

		Mesh::Texcoords& Mesh::GetTexcoords0()
		{
			return m_texcoords0;
		}
		
		Mesh::Indices& Mesh::GetIndices()
		{
			return m_indices;
		}

		uint32_t Mesh::GetSubMeshCount() const
		{
			return (uint32_t)m_subMeshes.size();
		}

		Mesh::SubMeshes& Mesh::GetSubMeshes()
		{
			return m_subMeshes;
		}

		MeshType Mesh::GetMeshType() const
		{
			return m_type;
		}

		void Mesh::SetTextureCount(uint32_t textureCount)
		{
			m_textureCount = textureCount;
		}

		uint32_t Mesh::GetTextureCount() const
		{
			return m_textureCount;
		}

		void Mesh::CreateIndexBuffer()
		{
			uint32_t subMeshCount = (uint32_t)m_subMeshes.size();

			// 部位それぞれのインデックスバッファ作成
			// マテリアル情報の定数バッファ作成
			for (uint32_t i = 0; i < subMeshCount; ++i)
			{
				auto subMesh = m_subMeshes[i];
				uint32_t* location = m_indices.data();

				location += subMesh->GetStartIndexLocation();
				uint32_t indexCount = subMesh->GetUseIndexCount();

				IndexBuffer* indexBuffer = new IndexBuffer();
				indexBuffer->SetCount(indexCount);
				indexBuffer->SetStride(sizeof(uint32_t));
				indexBuffer->Create(location);
				subMesh->SetIndexBuffer(indexBuffer);

				auto material = subMesh->GetMaterial();
				material->CreateConstantBuffer();

				auto texture = material->GetDecalTexture();
				
			}
		}

		void Mesh::SetVertexLayout(VertexLayout layout)
		{
			m_layout = layout;
		}

		void Mesh::AddVertexLayout(VertexLayout layout)
		{
			m_layout |= layout;
		}

		void Mesh::CreateVertexBuffer(uint32_t count, uint32_t stride, void* data, bool gpuAccess, ResourceViewType type)
		{
			VertexBuffer* vertexBuffer = new VertexBuffer(type);
			if (gpuAccess)
			{
				vertexBuffer->Dynamic(false);
				vertexBuffer->SetFlags(ResourceFlags::AllowUnorderedAccess);
			}
			vertexBuffer->SetStride(stride);
			vertexBuffer->SetCount(count);
			vertexBuffer->Create(data);

			m_vertexBuffers.push_back(vertexBuffer);
		}

		void Mesh::UpdateVertexBuffer(uint32_t index, void* data)
		{
			m_vertexBuffers[index]->Update(data);
		}
	}

}