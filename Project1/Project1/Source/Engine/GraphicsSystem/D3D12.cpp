#include "D3D12.h"
#include "D3D12/D3D12Device.h"
#include "HardwareBuffer/ResourceDescriptor.h"
#include "HardwareBuffer/ResourceView.h"
#include "HardwareBuffer/Resource.h"
#include "Texture/RenderTexture.h"
#include "Texture/DepthTexture.h"
#include "Enumerations/Include.h"
#include "Description/TextureDesc.h"
#include "HardwareCommand/GraphicsCommandList.h"
#include "HardwareCommand/GraphicsCommandQueue.h"
#include "HardwareCommand/ComputeCommandList.h"
#include "HardwareCommand/ComputeCommandQueue.h"

#include "DeviceFactory.h"
#include "DXGI/DXGISwapChain.h"

namespace Engine
{

	namespace GraphicsSystem
	{
		static D3D12Device* s_device = nullptr;
		static std::shared_ptr<RenderTexture> s_backBuffer[3] = {};
		static std::shared_ptr<DepthTexture> s_depth = nullptr;
		static std::shared_ptr<GraphicsCommandList> s_defaultList = nullptr;
		static std::shared_ptr<GraphicsCommandQueue> s_defaultQueue = nullptr;
		static DXGISwapChain* s_swapChain = nullptr;
		
		static std::shared_ptr<ComputeCommandList> s_defaultComputeList = nullptr;
		static std::shared_ptr<ComputeCommandQueue> s_defaultComputeQueue = nullptr;

		void Startup(void* hWnd, uint64_t width, uint64_t height)
		{
			DeviceFactory factory;
			auto adapter = factory.CreateAdapter();
			s_device = new D3D12Device(width, height, (IAdapter*)adapter);

			s_defaultQueue = GraphicsCommandQueue::Create("Graphics");
			s_defaultList = GraphicsCommandList::Create("Graphics");

			s_swapChain = factory.CreateSwapChain(hWnd, s_defaultQueue->GetInterface());

			for (uint32_t i = 0; i < 3; ++i)
			{
				char str[MAX_PATH];
				sprintf_s(str, "バックバッファ%d", i);
				s_backBuffer[i] = std::make_shared<RenderTexture>(str);
				
				Resource* resource = new Resource();
				resource->SetInterface(s_swapChain->GetBackBuffer(i));
				s_backBuffer[i]->SetResource(resource);
				s_backBuffer[i]->CreateRenderTargetView();
				RenderTexture::Register(str, s_backBuffer[i]);
				
			}
			
			s_depth = DepthTexture::Create("DefaultDepth", 1280, 960, ResourceFormat::Depth32);

			//s_defaultComputeList = ComputeCommandList::Create("Compute");
			//s_defaultComputeQueue = ComputeCommandQueue::Create("Compute");
		}

		D3D12Device* GetD3D12Device()
		{
			return s_device;
		}

		void Present()
		{
			s_swapChain->Present();
		}

		uint32_t GetCurrentIndex()
		{
			return s_swapChain->GetCurrentBackBufferIndex();
		}

		std::shared_ptr<RenderTexture> GetCurrentBackBuffer()
		{
			return s_backBuffer[s_swapChain->GetCurrentBackBufferIndex()];
		}

		std::shared_ptr<DepthTexture> GetDefaultDepthTexture()
		{
			return s_depth;
		}

		void Shutdown()
		{
			s_defaultQueue->WaitExecutionList();

			delete s_device;
		}
	}

}