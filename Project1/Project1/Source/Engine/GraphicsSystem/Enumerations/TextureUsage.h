#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// �e�N�X�`���̎g�p�@
		enum class TextureUsage : uint8_t
		{
			ShaderResource,	// �V�F�[�_�[���\�[�X
			RenderTarget,	// �����_�[�^�[�Q�b�g
			DepthStencil,	// �f�v�X�X�e���V��
		};

	}

}