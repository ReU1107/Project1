#pragma once

namespace Engine
{
	namespace PhysicsSystem
	{
		class PhysicsMaterial
		{
		private:
			float m_mass;				// ����
			float m_staticFriction;		// ���C�W��
			float m_dynamicFriction;	// ���C�W��
		public:
			// �R���X�g���N�^
			PhysicsMaterial();
			// �f�X�g���N�^
			~PhysicsMaterial();

		public:
			// ���ʐݒ�
			void SetMass(float mass);

			void SetRepulsiveForce(float);

			// ���C�W���ݒ�
			void SetStaticFriction(float friction);
			// 
			void SetDynamicFriction(float friction);

			// ���ʎ擾
			float GetMass() const;

			float GetStaticFriction() const;

			float GetDynamicFriction() const;

		};
	}
}