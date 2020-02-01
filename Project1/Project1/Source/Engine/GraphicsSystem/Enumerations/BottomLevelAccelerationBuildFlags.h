#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem
	{

		enum class BottomLevelAccelerationBuildFlags : uint8_t
		{
			AllowCompaction = 0x01,	// ���k����
			AllowUpdate = 0x02,		// �X�V����
			MinimizeMemory = 0x04,	// �������ŏ���
			PerformUpdate = 0x08,	// �X�V���s
			PreferFastBuild = 0x10,	// �f�����\�z
			PreferFastTrace = 0x20,	// �f�����g���[�X
		};
	}
}