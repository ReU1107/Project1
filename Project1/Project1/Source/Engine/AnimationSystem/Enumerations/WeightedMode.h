#pragma once
#include <cstdint>
namespace Engine 
{
	namespace AnimationSystem
	{
		// ���d
		enum class WeightedMode : uint8_t
		{
			None,	// In,Out��weight���g�p���Ȃ�
			In,		// In��weight���g�p����
			Out,	// Out��weight���g�p����
			Both,	// In,Out��weight���g�p����
		};
	}
}