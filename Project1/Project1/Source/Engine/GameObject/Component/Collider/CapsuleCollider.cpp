#include "CapsuleCollider.h"

namespace Engine
{

	CapsuleCollider::CapsuleCollider() noexcept
		: base("CapsuleCollider", ColliderShape::Capsule)
		, m_localCenter(Vector3::Zero)
		, m_localDirection(Vector3::Zero)
		, m_localHeight(0.0f)
		, m_localRadius(0.0f)
	{
	}

	CapsuleCollider::~CapsuleCollider() noexcept
	{
	}

	void CapsuleCollider::SetLocalCenter(const Vector3& center)
	{
		m_isDirty = true;
		m_localCenter = center;
	}

	void CapsuleCollider::SetLocalDirection(const Vector3& direction)
	{
		m_isDirty = true;
		m_localDirection = direction;
	}

	void CapsuleCollider::SetLocalHeight(float height)
	{
		m_isDirty = true;
		m_localHeight = height;
	}

	void CapsuleCollider::SetLocalRadius(float radius)
	{
		m_isDirty = true;
		m_localRadius = radius;
	}

	float CapsuleCollider::GetLocalRadius() const
	{
		return m_localRadius;
	}

	float CapsuleCollider::GetLocalHeight() const
	{
		return m_localHeight;
	}

	void CapsuleCollider::CalculateAABB() const
	{
		if (IsDirty())
		{
			m_aabb.min = m_localCenter - (m_localDirection * m_localHeight) - m_localRadius;
			m_aabb.max = m_localCenter + (m_localDirection * m_localHeight) + m_localRadius;
			m_isDirty = false;
		}
	}
}