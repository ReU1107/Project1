#pragma once
#include <cstdint>

namespace Engine
{
	enum class RotationOrder : uint8_t
	{
		XYZ,	// x¨y¨z‚Ì‡”Ô‚Å‰ñ“]
		YZX,	// y¨z¨x‚Ì‡”Ô‚Å‰ñ“]
		ZXY,	// z¨x¨y‚Ì‡”Ô‚Å‰ñ“]
	};
}