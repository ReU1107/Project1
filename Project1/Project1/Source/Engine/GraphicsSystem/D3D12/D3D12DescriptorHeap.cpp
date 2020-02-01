#include "D3D12DescriptorHeap.h"
#include <d3d12.h>

namespace Engine
{

	namespace GraphicsSystem 
	{

		D3D12DescriptorHeap::D3D12DescriptorHeap()
			: m_native(nullptr)
			, m_count(0)
			, m_index(0)
			, m_type()
		{
		}

		D3D12DescriptorHeap::~D3D12DescriptorHeap()
		{
			m_native->Release();
		}

		void D3D12DescriptorHeap::Reset(uint32_t index)
		{
			m_index = index;
		}

		D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUHandle() const
		{
			return m_native->GetCPUDescriptorHandleForHeapStart();
		}

		D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetGPUHandle() const
		{
			return m_native->GetGPUDescriptorHandleForHeapStart();
		}
	}
}