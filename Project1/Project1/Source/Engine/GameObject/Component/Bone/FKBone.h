#pragma once
#include "Bone.h"

namespace Engine
{
	// Forward Kinematics(順運動学)
	// 特別何かするわけじゃなくIKと区別しやすいようにしてるだけ
	class FKBone : public Bone
	{
	private:
		using base = Bone;

	public:
		// コンストラクタ
		FKBone();
		// デストラクタ
		virtual ~FKBone();

	};
}
