#include "Collider.h"
#include "../RigidBody.h"
#include "../../../PhysicsSystem/PhysicsMaterial.h"

namespace Engine
{
	using namespace PhysicsSystem;

	std::vector<Collider::ColliderPtr> Collider::allColliders;

	Collider::Collider(const std::string& name, ColliderShape shape) noexcept
		: base(name)
		, m_aabb()
		, m_material(nullptr)
		, m_rigidBody(nullptr)
		, m_shape(shape)
		, m_mask(0)
		, m_isDirty(true)
		, m_enabled(true)
	{
		m_material = std::make_shared<PhysicsMaterial>();
	}

	Collider::~Collider() noexcept
	{
	}

	void Collider::SetMask(uint32_t mask)
	{
		m_mask = mask;
	}

	void Collider::SetRigidBody(RigidBodyPtr rigidBody)
	{
		m_rigidBody = rigidBody;
	}

	Collider::RigidBodyPtr Collider::GetRigidBody() const
	{
		return m_rigidBody;
	}

	Collider::PhysicsMaterialPtr Collider::GetPhysicMaterial() const
	{
		return m_material;
	}

	const PhysicsSystem::AABB& Collider::GetAABB() const
	{
		CalculateAABB();
		return m_aabb;
	}

	uint32_t Collider::GetMask() const
	{
		return m_mask;
	}

	ColliderShape Collider::GetShape() const
	{
		return m_shape;
	}

	bool Collider::IsEnable() const
	{
		return m_enabled;
	}

	bool Collider::IsDirty() const
	{
		return m_isDirty;
	}

}