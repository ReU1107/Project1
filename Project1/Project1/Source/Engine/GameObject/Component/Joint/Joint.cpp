#include "Joint.h"

namespace Engine
{
	std::vector<Joint::JointPtr> Joint::allJoints;

	Joint::Joint(const std::string& name, JointType type) noexcept
		: base(name)
		, m_anchorPosition()
		, m_type(type)
		, m_enableCollision(true)
	{
	}

	Joint::~Joint() noexcept
	{
		m_connectedBones.clear();
	}

	void Joint::SetAnchorPosition(const Vector3& anchor)
	{
	}

	void Joint::AddConnectBone(GameObjectPtr bone)
	{
		m_connectedBones.push_back(bone);
	}

	JointType Joint::GetType() const
	{
		return m_type;
	}
}