#pragma once
#include <cstdint>
namespace Engine 
{
	// �V���h�E�L���X�e�B���O���@
	enum class ShadowCastingMode : uint8_t
	{
		Off,			// �e�𗎂Ƃ��Ȃ�
		On,				// �e�𗎂Ƃ�
		TwoSided,		// �H
		ShadowsOnly,	// �e�𗎂Ƃ������݂��Ȃ����̂Ƃ��Ĉ���(�e�͌����邪���̂͌����Ȃ�)
	};
}
