#pragma once
#include <cstdint>

namespace Engine
{

	namespace AudioSystem
	{

		enum class AudioEffectLayout : uint16_t
		{
			LowPassFilter = 0x000001,	// ����g���ʉ�
			HighPassFilter = 0x000002,	// �����g���ʉ�
			Reverb
		};

	}

}