#include "DeviceFactory.h"
#include "DXGI/DXGIFactory.h"
#include "DXGI/DXGIAdapter.h"
#include "DXGI/DXGISwapChain.h"
#include "Description/SwapChainDesc.h"
#include "Enumerations/ResourceFormat.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		DeviceFactory::DeviceFactory()
			: m_interface(nullptr)
		{
			m_interface = new DXGIFactory();
		}

		DeviceFactory::~DeviceFactory()
		{
			delete m_interface;
		}

		DXGIAdapter* DeviceFactory::CreateAdapter()
		{
			return (DXGIAdapter*)m_interface->CreateAdapter();
		}

		DXGISwapChain* DeviceFactory::CreateSwapChain(void* hWnd, ICommandQueue* queue)
		{
			SwapChainDesc desc = {};
			desc.count = 3;
			desc.format = ResourceFormat::RGBAUnorm;
			desc.hWnd = hWnd;
			desc.width = 1280;
			desc.height = 960;
			desc.queue = queue;
			return (DXGISwapChain*)m_interface->CreateSwapChain(desc);
		}
	}
}