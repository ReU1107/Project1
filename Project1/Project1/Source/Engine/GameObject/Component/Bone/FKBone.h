#pragma once
#include "Bone.h"

namespace Engine
{
	// Forward Kinematics(���^���w)
	// ���ʉ�������킯����Ȃ�IK�Ƌ�ʂ��₷���悤�ɂ��Ă邾��
	class FKBone : public Bone
	{
	private:
		using base = Bone;

	public:
		// �R���X�g���N�^
		FKBone();
		// �f�X�g���N�^
		virtual ~FKBone();

	};
}
