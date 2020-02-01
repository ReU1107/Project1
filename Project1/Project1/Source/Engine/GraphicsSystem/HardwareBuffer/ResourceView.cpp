#include "ResourceView.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Description/ResourceViewDesc.h"
#include "ResourceDescriptor.h"
#include "Resource.h"
#include "Buffer.h"
#include "..//Interface/IResourceView.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		ResourceView::ResourceView()
			: m_interface(nullptr)
			, m_type()
		{
		}

		ResourceView::~ResourceView()
		{
			delete m_interface;
		}

		ResourceView* ResourceView::Create(ResourceDescriptor* descriptor, Resource* resource, ResourceViewType type)
		{
			ResourceViewDesc desc = {};
			desc.descriptorHeap = descriptor->GetInterface();
			desc.resource = resource->GetInterface();
			desc.type = type;
			ResourceView* view = new ResourceView();
			view->m_type = type;
			view->m_interface = GetD3D12Device()->CreateResourceView(desc);

			return view;
		}

		ResourceView* ResourceView::Create(ResourceDescriptor* descriptor, Buffer* buffer, ResourceViewType type)
		{
			ResourceViewDesc desc = {};
			desc.descriptorHeap = descriptor->GetInterface();
			desc.resource = buffer->GetInterface();
			desc.type = type;
			desc.stride = buffer->GetStride();
			desc.isRaw = buffer->IsRaw();
			ResourceView* view = new ResourceView();
			view->m_type = type;
			view->m_interface = GetD3D12Device()->CreateResourceView(desc);

			return view;
		}

		ResourceView* ResourceView::Create(IDescriptorHeap* heap, IResource* lowResource, ResourceViewType type)
		{
			ResourceViewDesc desc = {};
			desc.descriptorHeap = heap;
			desc.resource = lowResource;
			desc.type = type;
			ResourceView* view = new ResourceView();
			view->m_type = type;
			view->m_interface = GetD3D12Device()->CreateResourceView(desc);

			return view;
		}

		ResourceView* ResourceView::Create(ResourceViewType type)
		{
			ResourceView* view = new ResourceView();
			view->m_type = type;
			view->m_interface = GetD3D12Device()->CreateResourceView();

			return view;
		}

		void ResourceView::Recreate(ResourceDescriptor* descriptor, Resource* resource)
		{
			Recreate(descriptor->GetInterface(), resource->GetInterface());
		}

		void ResourceView::Recreate(ResourceDescriptor* descriptor, Buffer* buffer)
		{
			ResourceViewDesc desc = {};
			desc.descriptorHeap = descriptor->GetInterface();
			desc.resource = buffer->GetInterface();
			desc.type = m_type;
			desc.isRaw = buffer->IsRaw();
			desc.stride = buffer->GetStride();

			GetD3D12Device()->RecreateResourceView(m_interface, desc);
		}

		void ResourceView::Recreate(IDescriptorHeap* heap, IResource* lowResource)
		{
			ResourceViewDesc desc = {};
			desc.descriptorHeap = heap;
			desc.resource = lowResource;
			desc.type = m_type;
			
			GetD3D12Device()->RecreateResourceView(m_interface, desc);
		}

		IResourceView* ResourceView::GetInterface() const
		{
			return m_interface;
		}
	}
}