#include "Buffer.h"
#include "../Description/BufferDesc.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Interface/IResource.h"
#include "../Enumerations/Include.h"

#include "../../Utility/EnumOperator.h"
#include "ResourceDescriptor.h"
#include "ResourceView.h"

namespace Engine 
{
	namespace GraphicsSystem 
	{

		Buffer::Buffer(ResourceViewType type)
			: m_interface(nullptr)
			, m_copyable(nullptr)
			, m_view(nullptr)
			, m_stride(0)
			, m_count(0)
			, m_size(0)
			, m_states(ResourceStates::GenericRead)
			, m_flags()
			, m_viewType(type)
			, m_isDynamic(true)
			, m_isRaw(true)
		{
			m_view = ResourceView::Create(type);
		}

		Buffer::~Buffer()
		{
			//delete m_view;
			delete m_copyable;
			delete m_interface;
		}

		void Buffer::SetStride(uint64_t stride)
		{
			m_stride = stride;
		}

		void Buffer::SetCount(uint64_t count)
		{
			m_count = count;
		}

		void Buffer::SetSize(uint64_t size)
		{
			m_size = size;
		}

		void Buffer::SetStates(ResourceStates states)
		{
			m_states = states;
		}

		void Buffer::SetFlags(ResourceFlags flags)
		{
			m_flags = flags;
		}

		void Buffer::SetInterface(IResource* resource)
		{
			m_interface = resource;
		}

		void Buffer::Dynamic(bool dynamic)
		{
			m_isDynamic = dynamic;
		}

		void Buffer::Raw(bool raw)
		{
			m_isRaw = raw;
		}

		void Buffer::Create(void* data)
		{
			// サイズが0ならストライドxカウント
			if (!m_size)
				m_size = m_stride * m_count;
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

		void Buffer::RecreateResourceView(ResourceDescriptor* descriptor)
		{
			m_view->Recreate(descriptor, this);
		}

		uint8_t* Buffer::Map(uint64_t begin, uint64_t end)
		{
			return m_interface->Map(begin, end);
		}

		void Buffer::Unmap(uint64_t begin, uint64_t end)
		{
			m_interface->Unmap(begin, end);
		}

		void Buffer::Update(void* data, uint64_t begin, uint64_t end)
		{
			if (m_copyable)
				m_copyable->Update(data, begin, end);
			else
				m_interface->Update(data, m_size, begin, end);
		}

		void Buffer::SetName(const std::wstring& name)
		{
			ID3D12Resource1* resource = (ID3D12Resource1*)m_interface->GetNativeResource();
			resource->SetName(name.c_str());
		}

	}

}