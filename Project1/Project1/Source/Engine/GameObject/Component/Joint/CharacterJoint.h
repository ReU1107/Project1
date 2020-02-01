#pragma once
#include "Joint.h"
namespace Engine
{

	class CharacterJoint final : public Joint
	{
	private:
		using base = Joint;
	public:
		// 
		CharacterJoint() noexcept;
		// 
		~CharacterJoint() noexcept;

	};
}