#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// �J�����O���@
		enum class CullType : uint8_t
		{
			None,	// �J�����O�Ȃ�
			Front,	// �\�ʃJ�����O
			Back,	// ���ʃJ�����O
		};
	}
}