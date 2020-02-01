#pragma once
#include "Component.h"
#include "../../Math/Include.h"
#include "../../../../Library/bullet/Include/btBulletDynamicsCommon.h"

namespace Engine 
{

	enum class ForceMode : uint8_t
	{
		Force,			// 
		Acceleration,	// ����
		VelocityChange,	// ���x�ω�
		Impulse,		// ���i��
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
		Vector4 m_rotation;			// ��](�p��)
		Vector3 m_position;			// �ʒu
		Vector3 m_linerVelocity;	// ���i���x
		Vector3 m_angularVelocity;	// ��]���x

		float m_mass;				// ����
		float m_drag;				// ��R
		bool m_useGravity;			// �d�͂̉e�����󂯂邩
		bool m_isKinematic;			// true�̍ۂ�Transform���g�p���Ȃ�
	public:
		// �R���X�g���N�^
		RigidBody() noexcept;
		// �f�X�g���N�^
		virtual ~RigidBody() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::RigidBody; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID()const override { return InstanceID::RigidBody; }

	public:

		// �ʒu�ݒ�
		void SetPosition(const Vector3& position);

		// ��]�l�ݒ�
		void SetRotation(const Vector4& rotation);
		void SetRotation(const Vector3& euler);
		// ���i���x�ݒ�
		void SetLinerVelocity(const Vector3& velocity);
		// ��]���x�ݒ�
		void SetAngularVelocity(const Vector3& velocity);

		// ���ʐݒ�
		void SetMass(float mass);

		// ���C�W���ݒ�
		void SetDrag(float drag);


		void Apply();

	public:
		// �͂�������
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