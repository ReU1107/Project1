#include "SkeletalMesh.h"
#include "BlendShape.h"
#include "../HardwareBuffer/Include.h"
#include "../../Utility/EnumOperator.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		//static VertexBuffer* ver = nullptr;

		SkeletalMesh::SkeletalMesh(const std::string& name)
			: base(name, MeshType::Skeletal)
			, m_dirtyFlags()
			, m_vertexDataIsDirty(true)
		{

			//if (!ver)
			//{
			//	ver = new VertexBuffer();
			//	ver->SetCount(1);
			//	ver->SetStride(1);
			//	ver->Create();
			//	ver->SetStride(0);
			//}

			//m_vertexBuffers[CovertToBaseType(VertexAttribute::Tangents)] = ver;
			//m_vertexBuffers[CovertToBaseType(VertexAttribute::DeltaNormals)] = ver;
			//m_vertexBuffers[CovertToBaseType(VertexAttribute::DeltaTangents)] = ver;
			//m_vertexBuffers[CovertToBaseType(VertexAttribute::Texcoords1)] = ver;
			//m_vertexBuffers[CovertToBaseType(VertexAttribute::Texcoords2)] = ver;
			//m_vertexBuffers[CovertToBaseType(VertexAttribute::Texcoords3)] = ver;
		}

		SkeletalMesh::~SkeletalMesh()
		{
			m_blendShapes.clear();

			m_boneWeights.clear();

			m_texcoords1.clear();
			m_texcoords2.clear();
			m_texcoords3.clear();

			m_deltaPositions.clear();

		}

		void SkeletalMesh::AddBlendShapeFrame(BlendShapePtr blendShape)
		{
			m_blendShapes.push_back(blendShape);
		}

		uint32_t SkeletalMesh::GetBlendShapeFrameCount() const
		{
			return m_blendShapes.size();
		}

		int32_t SkeletalMesh::GetBlendShapeIndex(const std::string& name) const
		{
			int32_t index = 0;
			for (auto& blendShape : m_blendShapes)
			{
				if (blendShape->GetName() == name)
				{
					return index;
				}
				index++;
			}
			return -1;
		}

		void SkeletalMesh::SetDirtyFlags(VertexDirtyFlags flags)
		{
			m_dirtyFlags = flags;
			m_vertexDataIsDirty = true;
		}

		SkeletalMesh::BlendShapes& SkeletalMesh::GetBlendShapes()
		{
			return m_blendShapes;
		}

		SkeletalMesh::BlendShapePtr SkeletalMesh::GetBlendShapeFrame(const std::string& name) const
		{
			for (auto& blendShape : m_blendShapes)
			{
				if (blendShape->GetName() == name)
				{
					return blendShape;
				}
			}
			return nullptr;
		}

		SkeletalMesh::BlendShapePtr SkeletalMesh::GetBlendShapeFrame(uint32_t index) const
		{
			return m_blendShapes.at(index);
		}

		SkeletalMesh::Texcoords& SkeletalMesh::GetTexcoords0()
		{
			return m_texcoords0;
		}

		SkeletalMesh::Texcoords& SkeletalMesh::GetTexcoords1()
		{
			return m_texcoords1;
		}

		SkeletalMesh::Texcoords& SkeletalMesh::GetTexcoords2()
		{
			return m_texcoords2;
		}

		SkeletalMesh::Texcoords& SkeletalMesh::GetTexcoords3()
		{
			return m_texcoords3;
		}

		SkeletalMesh::Positions& SkeletalMesh::GetBasePositions()
		{
			return m_basePositions;
		}

		SkeletalMesh::DeltaPositions& SkeletalMesh::GetDeltaPositions()
		{
			return m_deltaPositions;
		}

		std::vector<BoneWeight>& SkeletalMesh::GetBoneWeights()
		{
			return m_boneWeights;
		}

		void SkeletalMesh::Update()
		{
			// 
			if (m_vertexDataIsDirty)
			{
				uint32_t index = 0;
				if ((m_layout & VertexLayout::Positions) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Positions) != 0)
					{
						UpdateVertexBuffer(index, m_positions.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::Normals) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Normals) != 0)
					{
						UpdateVertexBuffer(index, m_normals.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::Tangents) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Tangents) != 0)
					{
						//UpdateVertexBuffer(index, m_normals.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::BoneWeights) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::BoneWeights) != 0)
					{
						UpdateVertexBuffer(index, m_boneWeights.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::BasePositions) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::BasePositions) != 0)
					{
						UpdateVertexBuffer(index, m_basePositions.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::DeltaPositions) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::DeltaPositions) != 0)
					{
						UpdateVertexBuffer(index, m_deltaPositions.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::DeltaNormals) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::DeltaNormals) != 0)
					{
						UpdateVertexBuffer(index, m_deltaNormals.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::DeltaTangents) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::DeltaTangents) != 0)
					{
						UpdateVertexBuffer(index, m_deltaTangents.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::Texcoords0) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Texcoords0) != 0)
					{
						UpdateVertexBuffer(index, m_texcoords0.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::Texcoords1) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Texcoords1) != 0)
					{
						UpdateVertexBuffer(index, m_texcoords1.data());
					}
					index++;
				}
				if ((m_layout & VertexLayout::Texcoords2) != 0)
				{
					if ((m_dirtyFlags & VertexDirtyFlags::Texcoords2) != 0)
					{
						UpdateVertexBuffer(index, m_texcoords2.data());
					}
					index++;
				}
				m_vertexDataIsDirty = false;
			}
		}

		void SkeletalMesh::CreateVertexBuffes()
		{
			if (m_vertexCountIsDirty)
			{
				if ((m_layout & VertexLayout::Positions) != 0)
				{
					CreateVertexBuffer((uint32_t)m_positions.size(), sizeof(Vector3), (void*)m_positions.data(), true, ResourceViewType::UnorderedAccess);
				}
				if ((m_layout & VertexLayout::Normals) != 0)
				{
					CreateVertexBuffer((uint32_t)m_normals.size(), sizeof(Vector3), (void*)m_normals.data(), true);
				}
				if ((m_layout & VertexLayout::Tangents) != 0)
				{
					//CreateVertexBuffer(VertexAttribute::Positions, m_positions.size(), sizeof(Vector3), .data());
				}
				if ((m_layout & VertexLayout::BoneWeights) != 0)
				{
					CreateVertexBuffer((uint32_t)m_boneWeights.size(), sizeof(BoneWeight), (void*)m_boneWeights.data(), true);
				}
				if ((m_layout & VertexLayout::BasePositions) != 0)
				{
					CreateVertexBuffer((uint32_t)m_basePositions.size(), sizeof(Vector3), (void*)m_basePositions.data(), true);
				}
				if ((m_layout & VertexLayout::DeltaPositions) != 0)
				{
					CreateVertexBuffer((uint32_t)m_deltaPositions.size(), sizeof(Vector3), (void*)m_deltaPositions.data(), true);
				}
				if ((m_layout & VertexLayout::DeltaNormals) != 0)
				{
					CreateVertexBuffer((uint32_t)m_deltaNormals.size(), sizeof(Vector3), (void*)m_deltaNormals.data(), true);
				}
				if ((m_layout & VertexLayout::DeltaTangents) != 0)
				{
					CreateVertexBuffer((uint32_t)m_deltaTangents.size(), sizeof(Vector3), (void*)m_deltaTangents.data(), true);
				}
				if ((m_layout & VertexLayout::Texcoords0) != 0)
				{
					CreateVertexBuffer((uint32_t)m_texcoords0.size() / 2, sizeof(Vector2), (void*)m_texcoords0.data(), true);
				}
				if ((m_layout & VertexLayout::Texcoords1) != 0)
				{
					CreateVertexBuffer((uint32_t)m_texcoords1.size(), sizeof(Vector2), (void*)m_texcoords1.data(), true);
				}
				if ((m_layout & VertexLayout::Texcoords2) != 0)
				{
					CreateVertexBuffer((uint32_t)m_texcoords2.size(), sizeof(Vector2), (void*)m_texcoords2.data(), true);
				}
				if ((m_layout & VertexLayout::Texcoords3) != 0)
				{
					CreateVertexBuffer((uint32_t)m_texcoords3.size(), sizeof(Vector2), (void*)m_texcoords3.data(), true);
				}
				m_vertexCountIsDirty = false;
			}

		}
	}
}
