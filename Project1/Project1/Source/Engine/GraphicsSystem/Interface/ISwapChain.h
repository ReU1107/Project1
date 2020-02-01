#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IResource;

		class ISwapChain
		{
		public:
			virtual ~ISwapChain() {}

			virtual IResource* GetBackBuffer(uint32_t index) const = 0;

			virtual uint32_t GetCurrentBackBufferIndex() const = 0;

			virtual void Present() const = 0;

		};
	}
}