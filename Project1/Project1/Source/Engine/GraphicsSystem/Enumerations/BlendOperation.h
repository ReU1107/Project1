#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BlendOperation : uint8_t
		{
			Addition,			// ����
			Subtract,			// ����(2����1��)
			ReverseSubtract,	// ����(1����2��)
			Min,				// �������l���̗p
			Max,				// �傫���l���̗p
		};
	}
}