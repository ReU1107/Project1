#pragma once
#include <cstdint>
/*
����
1����Lerp�u�����f�B���O
2����Lerp�u�����f�B���O
�O�p�`2����Lerp�u�����f�B���O
��ʉ�2����Lerp�u�����f�B���O
*/

/*
1�����̏ꍇ2�̃A�j���[�V�������u�����h�ł���
�u�����h�W����1����1��1.0 - 1�ڂ̃u�����h�W��
2�����̏ꍇ3,4�̃A�j���[�V�������u�����h�ł���
�u�����h�W����2��

*/

namespace Engine
{
	namespace AnimationSystem
	{
		// �A�j���[�V�����u�����f�B���O�A���S���Y��
		enum class BlendTreeType : uint8_t
		{
			Simple1D,				// �P��p�����[�^�̌^���g�p������{�I�ȃu�����f�B���O
			SimpleDirectional2D,	// ���[�V�������قȂ������\���ꍇ�ɍœK�B
			FreeformDirectional2D,	// ���̃u�����h�^�C�v�́A���[�V�������قȂ������\���Ƃ��Ɏg���܂�
			FreeformCartesian2D,	// ���[�V�������قȂ������\���Ȃ��ꍇ�ɍœK�ł��B
			Direct,					// �e�m�[�h�̃u�����f�B���O�E�F�C�g�𒼐ڃ��[�U�[�����䂷�邱�Ƃ��ł��܂�
		};
	}
}