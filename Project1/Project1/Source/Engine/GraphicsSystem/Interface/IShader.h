#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IShader
		{
		public:
			virtual ~IShader() {}

			// SDK依存シェーダー取得
			virtual void* GetNativeShader() const = 0;
			// バッファポインタ取得
			virtual void* GetBuffer() const = 0;
			// バッファサイズ取得
			virtual uint64_t GetSize() const = 0;
		};
	}
}