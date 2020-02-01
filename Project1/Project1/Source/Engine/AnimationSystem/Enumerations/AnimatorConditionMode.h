#pragma once
#include <cstdint>

/*
If,IfNot
�̎��̒��ӎ����Ƃ���
If�̏����Ɍ������ꍇ
�ϐ��ɓ����Ă���l��0�ȊO�̎���true�ɂȂ�
IfNot�̏ꍇ
���̋t��0�̎��̂�true�Ƃ���true�ɂȂ�
*/

namespace Engine
{
	namespace AnimationSystem
	{
		enum class AnimatorConditionMode : uint8_t
		{
			If,			// �p�����[�^�l�� true �̂Ƃ��A������ true �ɂȂ�܂��B
			IfNot,		// �p�����[�^�l�� false �̂Ƃ��A������ true �ɂȂ�܂��B
			Greater,	// �p�����[�^�l�� threshold ���傫���Ƃ��A������ true �ɂȂ�܂��B
			Less,		// �p�����[�^�l�� threshold �̒l�ȉ��̂Ƃ��A������ true �ɂȂ�܂��B
			Equals,		// �p�����[�^�l�� threshold �̒l�Ɠ������Ƃ��A������ true �ɂȂ�܂��B
			NotEqual,	// �p�����[�^�l�� threshold �̒l�Ɠ������Ȃ��Ƃ��A������ true �ɂȂ�܂��B
		};
	}
}
