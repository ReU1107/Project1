#include "DXGIFactory.h"
#include <dxgi1_6.h>
#include "DXGIAdapter.h"
#include "DXGISwapChain.h"
#include "../Description/SwapChainDesc.h"
#include "..//D3D12/D3D12Device.h"
#include "..//D3D12/D3D12CommandQueue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		DXGIFactory::DXGIFactory()
		{
			UINT flag = 0;
#if _DEBUG
			//flag |= DXGI_CREATE_FACTORY_DEBUG;
#endif
			auto hr = CreateDXGIFactory2(flag, IID_PPV_ARGS(&m_nativeFactory));

		}

		DXGIFactory::~DXGIFactory()
		{
			m_nativeFactory->Release();
		}

		IAdapter* DXGIFactory::CreateAdapter() const
		{
			/*
			EnumAdapterByGpuPreference
			第二引数にハイパフォーマンスを設定すると
			一番最初にパソコン内に入っているGPUで一番いいものが列挙される
			enum class Perfomance
			{
				High,	//
				Low		//
			}
			でどちらを選ぶか指定できるようにする
			*/
			bool performance = true;
			DXGI_GPU_PREFERENCE per = DXGI_GPU_PREFERENCE_UNSPECIFIED;

			IDXGIAdapter4* nativeAdapter = nullptr;
			per = performance ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_MINIMUM_POWER;

			m_nativeFactory->EnumAdapterByGpuPreference(0, per, IID_PPV_ARGS(&nativeAdapter));

			DXGIAdapter* adapter = new DXGIAdapter();
			adapter->m_nativeAdapter = nativeAdapter;

			return adapter;
		}

		ISwapChain* DXGIFactory::CreateSwapChain(const SwapChainDesc& desc) const
		{
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
			swapChainDesc.BufferCount = desc.count;
			swapChainDesc.Width = desc.width;
			swapChainDesc.Height = desc.height;
			swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc.SampleDesc.Count = 1;

			desc.queue;

			IDXGISwapChain1* tmpSwapChain = nullptr;
			m_nativeFactory->CreateSwapChainForHwnd((IUnknown*)desc.queue->GetNativeQueue(), (HWND)desc.hWnd,
				&swapChainDesc, nullptr, nullptr, &tmpSwapChain);

			IDXGISwapChain4* nativeSwapChain = nullptr;
			tmpSwapChain->QueryInterface(IID_PPV_ARGS(&nativeSwapChain));

			DXGISwapChain* swapChain = new DXGISwapChain();
			swapChain->m_nativeSwapChain = nativeSwapChain;

			return swapChain;
		}
	}
}