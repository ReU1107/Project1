#include "BottomLevelAccelerationStructure.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		BottomLevelAccelerationStructure::BottomLevelAccelerationStructure()
			: base()
			, m_flags(BottomLevelAccelerationStructureFlags::Opaque)
			, m_buildFlags(BottomLevelAccelerationBuildFlags::PreferFastTrace)
			, m_isDirty(true)
		{
		}

		BottomLevelAccelerationStructure::~BottomLevelAccelerationStructure()
		{
		}

		void BottomLevelAccelerationStructure::SetMaterialIndex(uint32_t index)
		{
			m_materialIndex = index;
		}

		void BottomLevelAccelerationStructure::AddSubBottomLevelASDesc(const SubBottomLevelAccelerationStructureDesc& desc)
		{
			m_descs.push_back(desc);
		}

		void BottomLevelAccelerationStructure::AddTraianglesGeometry(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, ConstantBuffer* constantBuffer)
		{
			SubBottomLevelAccelerationStructureDesc desc = {};
			desc.type = BottomLevelType::Traiangles;
			desc.vertexBuffer = vertexBuffer->GetInterface();
			desc.vertexCount = vertexBuffer->GetCount();
			desc.vertexStride = vertexBuffer->GetStride();
			desc.vertexFormat = vertexBuffer->GetFormat();
			m_vertexBuffers.push_back(vertexBuffer);

			// インデックスバッファがあるなら
			if (indexBuffer) 
			{
				desc.indexBuffer = indexBuffer->GetInterface();
				desc.indexCount = indexBuffer->GetCount();
				desc.indexFormat = indexBuffer->GetFormat();
			}
			// 定数バッファがあるなら
			if (constantBuffer) 
			{
				desc.constantBuffer = constantBuffer->GetInterface();
			}

			AddSubBottomLevelASDesc(desc);
		}

		void BottomLevelAccelerationStructure::AddProceduralGeometry(Buffer* buffer, ConstantBuffer* constantBuffer)
		{
			SubBottomLevelAccelerationStructureDesc desc = {};
			desc.type = BottomLevelType::Procedural;
			desc.aabbBuffer = buffer->GetInterface();
			desc.aabbCount = buffer->GetCount();
			desc.aabbStride = buffer->GetStride();

			// 定数バッファがあるなら
			if (constantBuffer)
			{
				desc.constantBuffer = constantBuffer->GetInterface();
			}

			AddSubBottomLevelASDesc(desc);
		}
		
		void BottomLevelAccelerationStructure::Create()
		{
			m_interface = GetD3D12Device()->CreateBottomLevelAccelerationStrcture();
		}
		
		void BottomLevelAccelerationStructure::Recreate()
		{
			if (!m_interface)
				Create();
			BottomLevelAccelerationStructureDesc desc = {};
			desc.flags = m_flags;
			desc.buildFlags = m_buildFlags;
			desc.subCount = m_descs.size();
			desc.subDescs = m_descs.data();

			GetD3D12Device()->RecreateBottomLevelAccelerationStructure(m_interface, desc);
			m_isDirty = true;
		}

		const BottomLevelAccelerationStructure::VertexBuffers& BottomLevelAccelerationStructure::GetVertexBuffers() const
		{
			return m_vertexBuffers;
		}
		
		uint32_t BottomLevelAccelerationStructure::GetMaterialIndex() const
		{
			return m_materialIndex;
		}

		void BottomLevelAccelerationStructure::SetBuildFlags(BottomLevelAccelerationBuildFlags buildFlags)
		{
			m_buildFlags = buildFlags;
		}

		uint32_t BottomLevelAccelerationStructure::GetContribution() const
		{
			return m_contribution;
		}

		uint32_t BottomLevelAccelerationStructure::GetID() const
		{
			return m_id;
		}

		uint32_t BottomLevelAccelerationStructure::GetMask() const
		{
			return m_mask;
		}

		bool BottomLevelAccelerationStructure::IsDirty() const
		{
			return m_isDirty;
		}

		void BottomLevelAccelerationStructure::Dirty(bool dirty)
		{
			m_isDirty = dirty;
		}
		
	}
}