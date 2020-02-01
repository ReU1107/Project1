#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// アバターにおいてマスクしている部位のタイプ
		enum class AvatarMaskBodyPart : uint16_t
		{
			Root = 0x0001,			// ルート
			Body = 0x0002,			// ボディ
			Head = 0x0004,			// 頭
			LeftLeg = 0x0008,		// 左脚
			RightLeg = 0x0010,		// 右脚
			LeftArm = 0x0020,		// 左腕
			RightArm = 0x0040,		// 右腕
			LeftFingers = 0x0080,	// 左手の指
			RightFingers = 0x0100,	// 右手の指
			LeftFootIK = 0x0200,	// 左足 IK
			RightFootIK = 0x0400,	// 右足 IK
			LeftHandIK = 0x0800,	// 左腕 IK
			RightHandIK = 0x1000,	// 右腕 IK
		};

		uint16_t GetBit(AvatarMaskBodyPart part);

	}
}