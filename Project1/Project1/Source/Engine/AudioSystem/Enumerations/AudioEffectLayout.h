#pragma once
#include <cstdint>

namespace Engine
{

	namespace AudioSystem
	{

		enum class AudioEffectLayout : uint16_t
		{
			LowPassFilter = 0x000001,	// ’áü”g”’Ê‰ß
			HighPassFilter = 0x000002,	// ‚ü”g”’Ê‰ß
			Reverb
		};

	}

}