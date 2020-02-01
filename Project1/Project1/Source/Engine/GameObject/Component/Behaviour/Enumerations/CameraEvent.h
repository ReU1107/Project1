#pragma once
#include <cstdint>

namespace Engine
{

	// �J�����̃R�}���h�o�b�t�@���s�^�C�~���O
	enum class CameraEvent
	{
		BeforeDepthTexture,			// �J�����̃f�v�X�e�N�X�`�������������O
		AfterDepthTexture,			// �J�����̃f�v�X�e�N�X�`�����������ꂽ��
		BeforeDepthNormalsTexture,	// �J�����̃f�v�X + �@���e�N�X�`�������������O
		AfterDepthNormalsTexture,	// �J�����̃f�v�X + �@���e�N�X�`�������������O
		BeforeGBuffer,				// �x�������_�����O��GBuffer�������_�����O�����O
		AfterGBuffer,				// �x�������_�����O��GBuffer�������_�����O���ꂽ��
		BeforeLighting,				// �x�������_�����O�� Lighting Pass �̑O
		AfterLighting,				// �x�������_�����O�� Lighting Pass �̌�
		BeforeFinalPass,			// �x�������_�����O�� Final Geometry Pass �̑O
		AfterFinalPass,				// �x�������_�����O�� Final Geometry Pass �̌�
		BeforeForwardOpaque,		// ���������_�����O�ŃI�y�[�N�I�u�W�F�N�g�̑O
		AfterForwardOpaque,			// ���������_�����O�ŃI�y�[�N�I�u�W�F�N�g�̌�
		BeforeImageEffectsOpaque,	// �I�y�[�N�I�u�W�F�N�g�ƃg�����X�y�A�����g�I�u�W�F�N�g�ԂŔ�������C���[�W�G�t�F�N�g�̑O
		AfterImageEffectsOpaque,	// �I�y�[�N�I�u�W�F�N�g�ƃg�����X�y�A�����g�I�u�W�F�N�g�ԂŔ�������C���[�W�G�t�F�N�g�̌�
		BeforeSkybox,				// �X�J�C�{�b�N�X��`�悷��O
		AfterSkybox,				// �X�J�C�{�b�N�X��`�悵����
		BeforeForwardAlpha,			// ���������_�����O�Ńg�����X�y�A�����g�I�u�W�F�N�g�̑O
		AfterForwardAlpha,			// ���������_�����O�Ńg�����X�y�A�����g�I�u�W�F�N�g�̌�
		BeforeImageEffects,			// �C���[�W�G�t�F�N�g�̑O
		AfterImageEffects,			// �C���[�W�G�t�F�N�g�̌�
		AfterEverything,			// �J���������ׂẴ����_�����O���s������
		BeforeReflections,			// �x�������_�����O�� Reflections Pass �̑O
		AfterReflections,			// �x�������_�����O�� Reflections Pass �̌�
		BeforeHaloAndLensFlares,	// �����Y�t���A�ƃu���b�P�����ۂ̑O
		AfterHaloAndLensFlares,		// �����Y�t���A�ƃu���b�P�����ۂ̌�
	};
}