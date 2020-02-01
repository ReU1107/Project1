#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// ��
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