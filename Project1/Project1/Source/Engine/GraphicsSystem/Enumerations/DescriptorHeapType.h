#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem
	{

		enum class DescriptorHeapType : uint8_t
		{
			Constant,			// �萔
			RenderTarget,		// �����_�[�^�[�Q�b�g
			DepthStencil,		// �f�v�X�X�e���V��
			ShaderResource,		// �V�F�[�_�[���\�[�X(�萔�Ɠ���)
			UnorderedAccess,	// �A���I�[�_�[�h�A�N�Z�X(�萔�Ɠ���)
			Sampler,			// �T���v���[
		};
	}
}