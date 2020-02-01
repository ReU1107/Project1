#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// Ž²
		enum class Axis : uint8_t
		{
			None,	// 
			X,		// 
			Y,		// 
			Z,		// 
		};

		uint8_t GetIndex(Axis axis);
	}
}