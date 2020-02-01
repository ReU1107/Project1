#include "IKBone.h"

namespace Engine
{
	IKBone::IKBone()
		: base("IKBone", BoneType::InverseKinematics)
		, m_effectorBone(nullptr)
		, m_links()
		, m_iterationCount(0)
		, m_iterationLimitAngle(0.0f)
	{
	}

	IKBone::~IKBone()
	{
	}
	
	void IKBone::SetEffectorBone(BonePtr bone)
	{
		m_effectorBone = bone;
	}
	
	void IKBone::AddLink(const IKLink& link)
	{
		m_links.push_back(link);
	}
	
	void IKBone::SetIterationCount(uint32_t loopCount)
	{
		m_iterationCount = loopCount;
	}

	void IKBone::SetIterationLimitAngle(float angle)
	{
		m_iterationLimitAngle = angle;
	}

	IKBone::BonePtr IKBone::GetEffectorBone() const
	{
		return m_effectorBone;
	}

	uint32_t IKBone::GetIterationCount() const
	{
		return m_iterationCount;
	}

	float IKBone::GetIterationLimitAngle() const
	{
		return m_iterationLimitAngle;
	}

	const IKBone::Links& IKBone::GetLinks() const
	{
		return m_links;
	}
}