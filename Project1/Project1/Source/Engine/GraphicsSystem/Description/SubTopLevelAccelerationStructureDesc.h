#pragma once
#include <cstdint>
#include "../../Math/Matrix4x4.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IAccelerationStructure;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		struct SubTopLevelAccelerationStructureDesc
		{
			IAccelerationStructure* bottom;					// �g�p����`��
			Matrix4x4 matrix;								// �g�p����s��
			uint32_t id;									// ���ʔԍ�(24bit)
			uint32_t contribution;							// �V�F�[�_�[���R�[�h�ԍ�
			uint8_t mask = 0xff;							// �}�X�N�l(8bit)
			SubTopLevelAccelerationStructureFlags flags;	// �t���O(8bit)
		};
	}
}