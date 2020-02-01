#include "Resource.h"
#include "..//D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "..//Description/TextureDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		Resource::Resource()
			: m_interface(nullptr)
			, m_states()
		{
		}

		Resource::~Resource()
		{
			delete m_interface;
		}

		Resource* Resource::Create(const TextureDesc& desc)
		{
			Resource* resource = new Resource();
			auto inter = GetD3D12Device()->CreateTexture(desc);
			resource->m_interface = inter;
			resource->m_states = desc.states;
			return resource;
		}

		void Resource::SetStates(ResourceStates states)
		{
			m_states = states;
		}

		void Resource::SetInterface(IResource* resource)
		{
			m_interface = resource;
		}

		IResource* Resource::GetInterface() const
		{
			return m_interface;
		}

		ResourceStates Resource::GetStates() const
		{
			return m_states;
		}
	}
}