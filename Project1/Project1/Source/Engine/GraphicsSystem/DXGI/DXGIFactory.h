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
			// コンストラクタ
			DXGIFactory();
			// デストラクタ
			virtual ~DXGIFactory();

			IAdapter* CreateAdapter() const;

			ISwapChain* CreateSwapChain(const SwapChainDesc& desc) const;
		};
	}
}