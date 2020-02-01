#pragma once
#include <cstdint>

namespace Engine 
{

	namespace AudioSystem
	{

		// デジタルオーディオフォーマット
		enum class DigitalFormat : uint32_t
		{
			PCM,
			LPCM,
		};

	}

}