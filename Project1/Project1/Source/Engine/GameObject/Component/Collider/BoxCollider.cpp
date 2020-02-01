#include "BoxCollider.h"

namespace Engine 
{

	BoxCollider::BoxCollider() noexcept
		: base("BoxCollider", ColliderShape::Box)
		, m_localCenter(Vector3::Zero)
		, m_localSize(Vector3::Zero)
	{
	}

	BoxCollider::~BoxCollider() noexcept
	{
	}

	void BoxCollider::SetLocalCenter(const Vector3& center)
	{
		m_isDirty = true;
		m_localCenter = center;
	}

	void BoxCollider::SetLocalSize(const Vector3& size)
	{
		m_isDirty = true;
		m_localSize = size;
	}

	Vector3 BoxCollider::GetHalfExtents() const
	{
		return Vector3();
	}

	void BoxCollider::CalculateAABB() const
	{
		if (IsDirty())
		{
			m_aabb.min = m_localCenter - m_localSize;
			m_aabb.max = m_localCenter + m_localSize;
			m_isDirty = false;
		}
	}

}