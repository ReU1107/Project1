#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// �A�j���[�V�����̃t���[���O�̏������@
		enum class WrapMode : uint8_t
		{
			Once,			// �^�C�����A�j���[�V�����̍Ō�ɒB����ƁA�N���b�v�͎����I�Ƀv���C���~���A�^�C�����N���b�v�̎n�߂Ƀ��Z�b�g�����
			Loop,			// �^�C�����A�j���[�V�����N���b�v�̍Ō�ɒB����ƁA�^�C���͍ŏ��ɖ߂胋�[�v����
			PingPong,		// �^�C�����A�j���[�V�����N���b�v�̍Ō�ɒB����ƁA�^�C���͎n�߂ƏI���̊Ԃ��s���|���̂悤�ɍs��������
			Default,		// �O�����Đݒ肵�Ă�����Ԃ��g�p���܂��B
			ClampForever,	// �ʏ�̍Đ����s��ꂽ��A�Ō�̃t���[���̃A�j���[�V�������Đ����ꑱ���邱�ƂɂȂ��~���邱�Ƃ͂���܂���
		};

	}
}