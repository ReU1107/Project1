#pragma once
#include <cstdint>

namespace Engine
{

	// ���C�g�̃C�x���g�^�C�~���O
	enum class LightEvent
	{
		BeforeShadowMap,		// �V���h�E�}�b�v�������_�����O�����O
		AfterShadowMap,			// �V���h�E�}�b�v�������_�����O���ꂽ��
		BeforeScreenspaceMask,	// �f�B���N�V���i�����C�g�̃X�N���[����Ԃ̃V���h�E�}�X�N���v�Z�����O
		AfterScreenspaceMask,	// �f�B���N�V���i�����C�g�X�N���[����Ԃ̃V���h�E�}�X�N���v�Z���ꂽ��
		BeforeShadowMapPass,	// �V���h�E�}�b�v�p�X�������_�����O�����O
		AfterShadowMapPass,		// �V���h�E�}�b�v�p�X�������_�����O������
	};
}