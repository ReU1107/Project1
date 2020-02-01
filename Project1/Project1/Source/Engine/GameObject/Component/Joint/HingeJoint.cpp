#include "HingeJoint.h"

namespace Engine
{

	HingeJoint::HingeJoint() noexcept
		: base("HingeJoint", JointType::Hinge)
	{
	}

	HingeJoint::~HingeJoint() noexcept
	{
	}
}