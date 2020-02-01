#pragma once
#include <cstdint>
namespace Engine 
{
	namespace AnimationSystem
	{
		// 加重
		enum class WeightedMode : uint8_t
		{
			None,	// In,Outのweightを使用しない
			In,		// Inのweightを使用する
			Out,	// Outのweightを使用する
			Both,	// In,Outのweightを使用する
		};
	}
}