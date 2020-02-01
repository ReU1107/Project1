#include "ResourceDescriptor.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include "../Interface/IDescriptorHeap.h"
#include "../D3D12/D3D12DescriptorHeap.h"
#include "../D3D12/D3D12Enumeration.h"
#include "../D3D12/D3D12ResourceView.h"
#include "ResourceView.h"

namespace Engine
{

	namespace GraphicsSystem
	{
		ResourceDescriptor::ResourceDescriptor()
			: m_interface(nullptr)
			, m_type()
			, m_currentIndex(0)
			, m_maxCount(0)
		{

		}

		ResourceDescriptor::~ResourceDescriptor()
		{
			delete m_interface;
		}

		ResourceDescriptor* ResourceDescriptor::CreateShaderResource(uint32_t count, bool shaderAccess, uint32_t nodeMask)
		{
			return Create(DescriptorHeapType::ShaderResource, count, shaderAccess, nodeMask);
		}

		ResourceDescriptor* ResourceDescriptor::CreateRenderTarget(uint32_t count, uint32_t nodeMask)
		{
			return Create(DescriptorHeapType::RenderTarget, count, false, nodeMask);
		}

		ResourceDescriptor* ResourceDescriptor::CreateDepthStencil(uint32_t count, uint32_t nodeMask)
		{
			return Create(DescriptorHeapType::DepthStencil, count, false, nodeMask);
		}

		ResourceDescriptor* ResourceDescriptor::Create(DescriptorHeapType type, uint32_t count, bool shaderAccess, uint32_t nodeMask)
		{
			DescriptorHeapDesc desc = {};
			desc.type = type;
			desc.nodeMask = nodeMask;
			desc.shaderAccess = shaderAccess;
			desc.count = count;

			ResourceDescriptor* desccriptor = new ResourceDescriptor();
			desccriptor->m_interface = GetD3D12Device()->CreateDescriptorHeap(desc);
			desccriptor->m_maxCount = count;
			desccriptor->m_currentIndex = 0;
			desccriptor->m_type = type;

			return desccriptor;
		}

		void ResourceDescriptor::Reset(uint32_t index)
		{
			m_interface->Reset(index);
			m_currentIndex = 0;
		}

		void ResourceDescriptor::CopyView(ResourceView* view)
		{
			CopyView(view->GetInterface());
		}

		void ResourceDescriptor::CopyView(IResourceView* view)
		{
			ID3D12Device5* device = GetD3D12Device()->m_device;

			auto dview = (D3D12ResourceView*)view;
			if (dview->m_isCopy)
				return;
			auto type = D3D12DescriptorHeapType(m_type);

			auto heap = (D3D12DescriptorHeap*)m_interface;
			auto destCPUHandle = heap->GetCPUHandle();
			auto destGPUHandle = heap->GetGPUHandle();

			uint32_t size = device->GetDescriptorHandleIncrementSize(type);
			uint32_t index = heap->m_index++;
			uint64_t stride = (uint64_t)size * index;

			destCPUHandle.ptr += stride;
			destGPUHandle.ptr += stride;


			D3D12_CPU_DESCRIPTOR_HANDLE sourceCPUHandle = dview->m_cpuHandle;
			device->CopyDescriptorsSimple(1, destCPUHandle, sourceCPUHandle, type);

			dview->m_cpuHandle = destCPUHandle;
			dview->m_gpuHandle = destGPUHandle;
			dview->m_index = index;
			dview->m_isCopy = true;

		}

		void ResourceDescriptor::SetName(const std::wstring& name)
		{
			ID3D12DescriptorHeap* heap = (ID3D12DescriptorHeap*)m_interface->GetNativeHeap();
			heap->SetName(name.c_str());
		}
	}
}