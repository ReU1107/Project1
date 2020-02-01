#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BottomLevelAccelerationStructureFlags : uint8_t
		{
			None = 0x00,					// �w��Ȃ�
			Opaque = 0x01,					// �s����
		};
	}
}