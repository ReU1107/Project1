#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// �X�e���V���l�̌v�Z
		enum class StencilOperation : uint8_t
		{
			Keep,			// �X�e���V���f�[�^��ۑ�
			Zero,			// �X�e���V���f�[�^��0�ɐݒ�
			Replace,		// 
			IncrementClamp,	// �X�e���V����1���₵�@�N�����v����
			DecrementClamp,	// �X�e���V����1���炵�@�N�����v����
			Invert,			// �X�e���V���f�[�^�𔽓]
			IncrementWrap,	// �X�e���V���l��1���₵�@���b�v����
			DecrementWrap,	// �X�e���V���l��1���炵�@���b�v����
		};
	}
}