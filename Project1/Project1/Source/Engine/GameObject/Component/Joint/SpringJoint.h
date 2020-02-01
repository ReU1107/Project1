#pragma once
#include "Joint.h"
namespace Engine 
{

	class SpringJoint final : public Joint
	{
	private:
		using base = Joint;
	public:
		// �R���X�g���N�^
		SpringJoint() noexcept;
		// �f�X�g���N�^
		virtual ~SpringJoint() noexcept;
	};

	template<>
	inline std::shared_ptr<SpringJoint> Component::Create()
	{
		auto joint = std::make_shared<SpringJoint>();

		Joint::allJoints.push_back(joint);

		return joint;
	}

}