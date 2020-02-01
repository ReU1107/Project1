#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BlendOperation : uint8_t
		{
			Addition,			// 足す
			Subtract,			// 引く(2から1を)
			ReverseSubtract,	// 引く(1から2を)
			Min,				// 小さい値を採用
			Max,				// 大きい値を採用
		};
	}
}