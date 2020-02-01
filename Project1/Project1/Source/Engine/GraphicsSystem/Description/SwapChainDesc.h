#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class ResourceFormat : uint8_t;
		class IDevice;
		class ICommandQueue;

		struct SwapChainDesc
		{
			void* hWnd;				// ウィンドウハンドル
			ICommandQueue* queue;	// デバイス
			uint32_t width;			// 幅
			uint32_t height;		// 高さ
			uint32_t count;			// 数
			ResourceFormat format;	// フォーマット
		};
	}
}