#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// �A�o�^�[�ɂ����ă}�X�N���Ă��镔�ʂ̃^�C�v
		enum class AvatarMaskBodyPart : uint16_t
		{
			Root = 0x0001,			// ���[�g
			Body = 0x0002,			// �{�f�B
			Head = 0x0004,			// ��
			LeftLeg = 0x0008,		// ���r
			RightLeg = 0x0010,		// �E�r
			LeftArm = 0x0020,		// ���r
			RightArm = 0x0040,		// �E�r
			LeftFingers = 0x0080,	// ����̎w
			RightFingers = 0x0100,	// �E��̎w
			LeftFootIK = 0x0200,	// ���� IK
			RightFootIK = 0x0400,	// �E�� IK
			LeftHandIK = 0x0800,	// ���r IK
			RightHandIK = 0x1000,	// �E�r IK
		};

		uint16_t GetBit(AvatarMaskBodyPart part);

	}
}