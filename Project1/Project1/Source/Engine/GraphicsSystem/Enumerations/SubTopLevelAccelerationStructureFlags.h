#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class SubTopLevelAccelerationStructureFlags : uint8_t
		{
			None = 0x00,					// �w��Ȃ�
			CullDisable = 0x01,				// �J�����O�̉e�����󂯂Ȃ�
			FrontCounterClockwise = 0x02,	// �O�ʂ������̔z�u�̒��_�ɂȂ�
			Opaque = 0x04,					// �s����
			NonOpaque = 0x08,				// �s��������Ȃ�
		};
	}
}