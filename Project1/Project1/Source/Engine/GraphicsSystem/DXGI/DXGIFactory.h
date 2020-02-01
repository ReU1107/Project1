#pragma once
#include "..//Interface/IFactory.h"

struct IDXGIFactory7;
namespace Engine
{
	namespace GraphicsSystem
	{
		class IAdapter;
		class ISwapChain;
		struct SwapChainDesc;

		class DXGIFactory : public IFactory
		{
		private:
			IDXGIFactory7* m_nativeFactory;

		public:
			// �R���X�g���N�^
			DXGIFactory();
			// �f�X�g���N�^
			virtual ~DXGIFactory();

			IAdapter* CreateAdapter() const;

			ISwapChain* CreateSwapChain(const SwapChainDesc& desc) const;
		};
	}
}