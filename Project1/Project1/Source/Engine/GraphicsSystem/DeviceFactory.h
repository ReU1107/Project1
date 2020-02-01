#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class DXGIFactory;
		class DXGIAdapter;
		class DXGISwapChain;
		class ICommandQueue;

		class DeviceFactory
		{
		private:
			DXGIFactory* m_interface;
		public:
			// コンストラクタ
			DeviceFactory();
			// コンストラクタ
			~DeviceFactory();
			
			DXGIAdapter* CreateAdapter();

			DXGISwapChain* CreateSwapChain(void* hWnd, ICommandQueue* queue);
		};
	}
}