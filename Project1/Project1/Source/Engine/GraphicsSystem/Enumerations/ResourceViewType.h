#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		// ���\�[�X�r���[�̎��
		enum class ResourceViewType : uint8_t
		{
			ShaderResource,		// �V�F�[�_�[���\�[�X�r���[
			RenderTarget,		// �����_�[�^�[�Q�b�g�r���[
			DepthStencil,		// �f�v�X�X�e���V���r���[
			UnorderedAccess,	// �A���I�[�_�[�h�A�N�Z�X�r���[
			ConstantBuffer,		// �R���X�^���g�o�b�t�@�[�r���[
			Raytracing,			// ���C�g���[�V���O�p(SRV�Ɠ���)
		};

	}

}