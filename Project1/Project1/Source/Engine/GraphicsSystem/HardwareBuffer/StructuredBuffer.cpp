#include "StructuredBuffer.h"
#include "../Description/BufferDesc.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Enumerations/BufferType.h"
#include "../Interface/IResource.h"
#include "../Enumerations/Include.h"

#include "ResourceDescriptor.h"
#include "ResourceView.h"
#include "../Enumerations/ResourceViewType.h"
#include "../../Utility/EnumOperator.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		StructuredBuffer::StructuredBuffer(ResourceViewType type)
			: base(type)
		{
		}

		StructuredBuffer::~StructuredBuffer()
		{
			delete m_view;
		}

		//void StructuredBuffer::Create(void* data)
		//{
		//	// サイズが0ならストライドxカウント
		//	if (!m_size)
		//		m_size = m_stride * m_count;
		//	BufferDesc desc = {};
		//	desc.isDynamic = m_isDynamic;
		//	desc.state = m_states;
		//	desc.size = m_size;
		//	desc.flags = m_flags;
		//	m_states = ResourceStates::GenericRead;
		//	if ((m_flags & ResourceFlags::AllowUnorderedAccess) != 0)
		//	{
		//		m_isDynamic = false;
		//	}
		//	
		//	m_interface = GetD3D12Device()->CreateBuffer(desc);

		//	if (!m_isDynamic)
		//	{
		//		m_copyable = new StructuredBuffer();
		//		m_copyable->SetInterface(GetD3D12Device()->CreateCopyableResource(m_interface));
		//		m_copyable->SetStates(ResourceStates::GenericRead);
		//		m_copyable->SetSize(m_size);
		//		m_copyable->SetStride(m_stride);
		//		m_copyable->SetCount(m_count);
		//		m_copyable->SetFlags(ResourceFlags::None);
		//	}

		//	if (data)
		//	{
		//		if (m_copyable)
		//			m_copyable->Update(data, desc.size);
		//		else
		//		{
		//			m_interface->Update(data, desc.size);
		//		}
		//	}
		//}

	}
}