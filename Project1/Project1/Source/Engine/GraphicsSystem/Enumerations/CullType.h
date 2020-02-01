#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// カリング方法
		enum class CullType : uint8_t
		{
			None,	// カリングなし
			Front,	// 表面カリング
			Back,	// 裏面カリング
		};
	}
}