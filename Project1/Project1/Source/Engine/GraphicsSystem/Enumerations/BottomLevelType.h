#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BottomLevelType : uint8_t 
		{
			Traiangles,		// 三角形
			Procedural,		// 任意の形状
		};

	}
}