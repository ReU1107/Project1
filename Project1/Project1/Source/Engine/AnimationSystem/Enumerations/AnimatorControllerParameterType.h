#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		enum class AnimatorControllerParameterType : uint8_t
		{
			Float,	// float 型のパラメーター
			Int,	// Int 型のパラメーター
			Bool,	// Boolean 型のパラメーター
			Trigger,// Trigger 型パラメーター
		};
	}
}