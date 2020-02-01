#include "PhysicsMaterial.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		PhysicsMaterial::PhysicsMaterial()
			: m_mass(0.0f)
			, m_staticFriction(0.0f)
		{
		}

		PhysicsMaterial::~PhysicsMaterial()
		{
		}
		
		void PhysicsMaterial::SetMass(float mass)
		{
			m_mass = mass;
		}

		void PhysicsMaterial::SetRepulsiveForce(float)
		{
		}

		void PhysicsMaterial::SetStaticFriction(float friction)
		{
		}
		
		void PhysicsMaterial::SetDynamicFriction(float friction)
		{
		}
		
		float PhysicsMaterial::GetMass() const
		{
			return m_mass;
		}

		float PhysicsMaterial::GetStaticFriction() const
		{
			return 0.0f;
		}

		float PhysicsMaterial::GetDynamicFriction() const
		{
			return 0.0f;
		}
	}
}