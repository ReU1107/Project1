#pragma once
#include "Joint.h"
namespace Engine 
{

	class HingeJoint final : public Joint
	{
	private:
		using base = Joint;
	public:
		// �R���X�g���N�^
		HingeJoint() noexcept;
		// �f�X�g���N�^
		virtual ~HingeJoint() noexcept;

	};

	template<>
	inline std::shared_ptr<HingeJoint> Component::Create()
	{
		auto joint = std::make_shared<HingeJoint>();

		Joint::allJoints.push_back(joint);

		return joint;
	}
}