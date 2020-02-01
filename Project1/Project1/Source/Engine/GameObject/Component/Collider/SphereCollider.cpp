#include "SphereCollider.h"

namespace Engine
{

	SphereCollider::SphereCollider() noexcept
		: base("SphereCollider", ColliderShape::Sphere)
		, m_localCenter(Vector3::Zero)
		, m_localRadius(0.0f)
	{
	}

	SphereCollider::~SphereCollider() noexcept
	{
	}

	void SphereCollider::SetLocalCenter(const Vector3& center)
	{
		m_isDirty = true;
		m_localCenter = center;
	}

	void SphereCollider::SetLocalRadius(float radius)
	{
		m_isDirty = true;
		m_localRadius = radius;
	}

	const Vector3& SphereCollider::GetLocalCenter() const
	{
		return m_localCenter;
	}

	float SphereCollider::GetLocalRadius() const
	{
		return m_localRadius;
	}

	void SphereCollider::CalculateAABB() const
	{
		if (IsDirty())
		{
			m_aabb.min = m_localCenter - m_localRadius;
			m_aabb.max = m_localCenter + m_localRadius;

			m_isDirty = false;
		}
	}
}