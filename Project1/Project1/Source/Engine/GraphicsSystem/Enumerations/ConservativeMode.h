#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 保守的って意味だけどよく分かってない
		// 後で調べます
		enum class ConservativeMode : uint8_t
		{
			Off,
			On,
		};
	}
}