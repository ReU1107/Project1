#pragma once
#include <cstdint>

namespace Engine
{

	// ���
	enum class LightType : uint8_t
	{
		Directional,	// ���s����(�w����)
		Point,			// �_����
		Spot,			// �X�|�b�g���C�g
		Area			// �G���A
	};
}