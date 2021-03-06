#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 比較関数
		enum class ComparisonFunction : uint8_t
		{
			Never,			// 全て不合格
			Less,			// 小きいなら合格
			Equal,			// 等しいなら合格
			LessEqual,		// 以下なら合格
			Greater,		// 大きいなら合格
			NotEqual,		// 等しくないなら合格
			GreaterEqual,	// 以上なら合格
			Always,			// 全て合格
		};
	}
}