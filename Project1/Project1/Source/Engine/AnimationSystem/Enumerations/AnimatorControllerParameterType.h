#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		enum class AnimatorControllerParameterType : uint8_t
		{
			Float,	// float �^�̃p�����[�^�[
			Int,	// Int �^�̃p�����[�^�[
			Bool,	// Boolean �^�̃p�����[�^�[
			Trigger,// Trigger �^�p�����[�^�[
		};
	}
}