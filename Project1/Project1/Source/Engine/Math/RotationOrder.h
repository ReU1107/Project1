#pragma once
#include <cstdint>

namespace Engine
{
	enum class RotationOrder : uint8_t
	{
		XYZ,	// x��y��z�̏��Ԃŉ�]
		YZX,	// y��z��x�̏��Ԃŉ�]
		ZXY,	// z��x��y�̏��Ԃŉ�]
	};
}