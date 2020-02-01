#pragma once
#include "Component.h"
#include "../../Math/Include.h"
#include "../../../../Library/bullet/Include/btBulletDynamicsCommon.h"

namespace Engine 
{

	enum class ForceMode : uint8_t
	{
		Force,			// 
		Acceleration,	// 加速
		VelocityChange,	// 速度変化
		Impulse,		// 推進力
	};

	class RigidBody final : public Component
	{
	private:
		using base = Component;
		using RigidBodyPtr = std::shared_ptr<RigidBody>;
	public:
		static std::vector<RigidBodyPtr> allRigidBodies;
	private:
		btRigidBody* m_bt;
		Vector4 m_rotation;			// 回転(姿勢)
		Vector3 m_position;			// 位置
		Vector3 m_linerVelocity;	// 平進速度
		Vector3 m_angularVelocity;	// 回転速度

		float m_mass;				// 質量
		float m_drag;				// 抵抗
		bool m_useGravity;			// 重力の影響を受けるか
		bool m_isKinematic;			// trueの際はTransformを使用しない
	public:
		// コンストラクタ
		RigidBody() noexcept;
		// デストラクタ
		virtual ~RigidBody() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::RigidBody; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID()const override { return InstanceID::RigidBody; }

	public:

		// 位置設定
		void SetPosition(const Vector3& position);

		// 回転値設定
		void SetRotation(const Vector4& rotation);
		void SetRotation(const Vector3& euler);
		// 平進速度設定
		void SetLinerVelocity(const Vector3& velocity);
		// 回転速度設定
		void SetAngularVelocity(const Vector3& velocity);

		// 質量設定
		void SetMass(float mass);

		// 摩擦係数設定
		void SetDrag(float drag);


		void Apply();

	public:
		// 力を加える
		void AddForce(const Vector3& force, ForceMode mode);
		void AddForce(float forceX, float forceY, float forceZ, ForceMode mode);



		const Vector3& GetLinerVelocity() const;

		const Vector3& GetAngularVelocity() const;
	};

	template<>
	inline std::shared_ptr<RigidBody> Component::Create()
	{
		auto rigidBody = std::make_shared<RigidBody>();

		RigidBody::allRigidBodies.push_back(rigidBody);

		return rigidBody;
	}
}

using RigidBodyPtr = std::shared_ptr<Engine::RigidBody>;