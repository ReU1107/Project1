#include "DXGISwapChain.h"
#include <dxgi1_6.h>
#include <d3d12.h>
#include "..//D3D12/D3D12Resource.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		DXGISwapChain::DXGISwapChain()
			: m_nativeSwapChain(nullptr)
		{

		}

		DXGISwapChain::~DXGISwapChain()
		{
			m_nativeSwapChain->Release();
		}

		IResource* DXGISwapChain::GetBackBuffer(uint32_t index) const
		{
			ID3D12Resource1* native = nullptr;
			m_nativeSwapChain->GetBuffer(index, IID_PPV_ARGS(&native));

			D3D12Resource* resource = new D3D12Resource();
			resource->m_nativeResource = native;

			return resource;
		}

		uint32_t DXGISwapChain::GetCurrentBackBufferIndex() const
		{
			return m_nativeSwapChain->GetCurrentBackBufferIndex();
		}

		void DXGISwapChain::Present() const
		{
			m_nativeSwapChain->Present(0, 0);
		}
	}
}