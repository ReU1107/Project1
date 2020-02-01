#include "SpringJoint.h"

namespace Engine
{

	SpringJoint::SpringJoint() noexcept
		: base("SpringJoint", JointType::Spring)
	{
	}

	SpringJoint::~SpringJoint() noexcept
	{
	}

}