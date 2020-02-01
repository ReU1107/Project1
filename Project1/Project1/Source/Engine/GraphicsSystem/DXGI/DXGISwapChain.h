#pragma once
#include "..//Interface/ISwapChain.h"

struct IDXGISwapChain4;

namespace Engine
{
	namespace GraphicsSystem
	{
		class DXGISwapChain : public ISwapChain
		{
		public:
			IDXGISwapChain4* m_nativeSwapChain;

		public:
			// �R���X�g���N�^
			DXGISwapChain();
			// �f�X�g���N�^
			virtual ~DXGISwapChain();

			virtual IResource* GetBackBuffer(uint32_t index) const override;

			virtual uint32_t GetCurrentBackBufferIndex() const override;

			virtual void Present() const override;
		};
	}
}