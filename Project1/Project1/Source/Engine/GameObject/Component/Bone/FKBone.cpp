#include "FKBone.h"

namespace Engine
{
	
	FKBone::FKBone()
		: base("FKBone", BoneType::ForwardKinematics)
	{
	}

	FKBone::~FKBone()
	{
	}
}