#pragma once

namespace Engine
{
	namespace PhysicsSystem
	{
		class PhysicsMaterial
		{
		private:
			float m_mass;				// 質量
			float m_staticFriction;		// 摩擦係数
			float m_dynamicFriction;	// 摩擦係数
		public:
			// コンストラクタ
			PhysicsMaterial();
			// デストラクタ
			~PhysicsMaterial();

		public:
			// 質量設定
			void SetMass(float mass);

			void SetRepulsiveForce(float);

			// 摩擦係数設定
			void SetStaticFriction(float friction);
			// 
			void SetDynamicFriction(float friction);

			// 質量取得
			float GetMass() const;

			float GetStaticFriction() const;

			float GetDynamicFriction() const;

		};
	}
}