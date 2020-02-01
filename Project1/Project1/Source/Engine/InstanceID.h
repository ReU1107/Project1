#pragma once
#include <cstdint>

namespace Engine
{
	// �I�u�W�F�N�g�N���X���p�����Ă��邻�ꂼ���ID
	// TypeID
	enum class InstanceID : uint32_t
	{
		Object,				// �I�u�W�F�N�g
		GameObject,			// �Q�[���I�u�W�F�N�g
		Motion,				// ���[�V����
		Shader,				// �V�F�[�_�[
		Texture,			// �e�N�X�`��
		Texture2D,			// 
		RenderTexture,		// �����_�[�e�N�X�`��
		DepthTexture,		// �f�v�X�e�N�X�`��
		Mesh,				// ���b�V��
		SubMesh,			// �T�u���b�V��
		Material,			// �}�e���A��
		BlendShape,			// �u�����h�V�F�C�v
		PhysicsMaterial,	// �������Z�p�ގ�
		Billboard,			// �r���{�[�h
		Sprite,				// �X�v���C�g
		Component,			// �R���|�[�l���g
		Transform,			// �ϊ�
		Behaviour,			// �����\�����N���X
		Animation,			// �A�j���[�V����
		Animator,			// �A�j���[�^�[
		Camera,				// �J����
		Light,				// ���C�g
		Terrain,			// �n�`
		SkyBox,				// �L���[�u�}�b�v
		MonoBehaviour,		// �X�N���v�g�̊��N���X
		Renderer,			// �����_���[�̊��N���X
		MeshRenderer,		// ���b�V���`��
		LineRenderer,		// ���C���`��
		SpriteRenderer,		// �X�v���C�g�`��
		RayTracer,			// ���C�g���[�T�[
		SkinnedMeshRenderer,// ���b�V���X�L�j���O
		Collider,			// �Փˌ��m�̊��N���X
		Filter,				// �t�B���^�[�̊��N���X
		RigidBody,			// ����(�������Z)
		SoftBody,			// ���(�������Z)
		Joint,				// �W���C���g(�֐�)�̊��N���X
		Bone,				// �{�[���N���X(�X�L�j���O�ɕK�v)
		AudioSource,		// �����N���X
		AudioListener,		// ���𕷂�
	};

	using TypeID = InstanceID;
}