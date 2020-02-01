#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderResourceType : uint8_t
		{
			ConstantBuffer,		// �萔�o�b�t�@
			ShaderResource,		// �V�F�[�_�[���\�[�X
			ReadWriteResource,	// �ǂݏ����\���\�[�X
			Sampler,			// �T���v���[
		};

	}

}