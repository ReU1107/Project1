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
			// �R���X�g���N�^
			DeviceFactory();
			// �R���X�g���N�^
			~DeviceFactory();
			
			DXGIAdapter* CreateAdapter();

			DXGISwapChain* CreateSwapChain(void* hWnd, ICommandQueue* queue);
		};
	}
}