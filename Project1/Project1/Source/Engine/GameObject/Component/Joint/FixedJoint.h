#pragma once
#include "Joint.h"
namespace Engine 
{

	class FixedJoint final : public Joint
	{
	private:
		using base = Joint;
	public:
		// 
		FixedJoint() noexcept;
		// 
		~FixedJoint() noexcept;

	};
}