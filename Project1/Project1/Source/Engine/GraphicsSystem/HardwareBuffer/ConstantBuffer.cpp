#include "ConstantBuffer.h"
#include "../Description/BufferDesc.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Enumerations/BufferType.h"
#include "../Interface/IResource.h"
#include "ResourceDescriptor.h"
#include "ResourceView.h"
#include "../Enumerations/ResourceViewType.h"

#include "../../Utility/Utility.h"
#include "../Enumerations/Include.h"

namespace Engine
{

	namespace GraphicsSystem 
	{

		ConstantBuffer::ConstantBuffer(ResourceViewType type)
			: base(type)
		{
		}

		ConstantBuffer::~ConstantBuffer()
		{
		}

		void ConstantBuffer::Create(void* data)
		{

			// �T�C�Y��0�Ȃ�X�g���C�hx�J�E���g
			// 256�o�C�g���E�ō쐬����K�v������
			if (!m_size)
				m_size = Alignment((m_stride * m_count), 256);
			BufferDesc desc = {};
			desc.isDynamic = m_isDynamic;
			desc.state = m_states;
			desc.size = m_size;
			desc.flags = m_flags;

			m_interface = GetD3D12Device()->CreateBuffer(desc);

			if (!m_isDynamic)
			{
				m_copyable = new Buffer(m_viewType);
				m_copyable->SetInterface(GetD3D12Device()->CreateCopyableResource(m_interface));
				m_copyable->SetStates(ResourceStates::GenericRead);
				m_copyable->SetSize(m_size);
				m_copyable->SetStride(m_stride);
				m_copyable->SetCount(m_count);
				m_copyable->IsDynamic();
				m_copyable->SetFlags(ResourceFlags::None);
			}

			if (data)
			{
				if (m_copyable)
					m_copyable->Update(data, desc.size);
				else
					m_interface->Update(data, desc.size);
			}

		}

	}
}