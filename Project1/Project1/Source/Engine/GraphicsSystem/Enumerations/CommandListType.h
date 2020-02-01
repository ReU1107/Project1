#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class CommandListType : uint8_t
		{
			General,	// �S�Đςݍ��݉\
			Copy,		// �R�s�[�̂�
			Compute,	// �R���s���[�g�֘A�̂�
		};

	}
}