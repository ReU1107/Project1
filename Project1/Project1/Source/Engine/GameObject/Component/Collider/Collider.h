#pragma once
#include "../Component.h"
#include "../../../Math/Vector3.h"
#include "../../../PhysicsSystem/AABB.h"

namespace Engine
{

	// �O���錾
	class RigidBody;

	namespace PhysicsSystem
	{
		class PhysicsMaterial;
	}

	// �R���C�_�[�̌`��
	enum class ColliderShape : uint8_t
	{
		Box,		// ��
		Capsule,	// �J�v�Z��
		Sphere,		// ��
		Mesh,		// ���b�V��
		Terrain		// �n�`
	};

	struct Collision
	{
		Vector3 relativeVelocity;	// �Փ˂���Collider���m�̑��ΓI�ȑ��x
		// �Փ˂���
	};

	// �R���C�_�[(�Փˑ��u)
	class Collider : public Component
	{
	private:
		using base = Component;
		using ColliderPtr = std::shared_ptr<Collider>;
		using PhysicsMaterialPtr = std::shared_ptr<PhysicsSystem::PhysicsMaterial>;
		using RigidBodyPtr = std::shared_ptr<RigidBody>;
	public:
		static std::vector<ColliderPtr> allColliders;
	protected:
		mutable PhysicsSystem::AABB m_aabb;
		PhysicsMaterialPtr m_material;		// ���̃R���C�_�[�̍ގ�
		RigidBodyPtr m_rigidBody;			// 
		ColliderShape m_shape;
		uint32_t m_mask;
		mutable bool m_isDirty;
		bool m_enabled;
	public:
		// �R���X�g���N�^
		Collider(const std::string& name, ColliderShape shape) noexcept;
		// �f�X�g���N�^
		virtual ~Collider() noexcept;
	public:
		// ID�擾
		static const InstanceID ID() { return InstanceID::Collider; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID()const override { return InstanceID::Collider; }

	public:

		// �}�X�N�l�ݒ�
		void SetMask(uint32_t mask);

		// ���W�b�g�{�f�B�ݒ�
		void SetRigidBody(RigidBodyPtr rigidBody);

		// ���W�b�g�{�f�B�擾
		RigidBodyPtr GetRigidBody() const;

		// �}�e���A���擾
		PhysicsMaterialPtr GetPhysicMaterial() const;

		// AABB�擾
		const PhysicsSystem::AABB& GetAABB() const;

		virtual void CalculateAABB() const = 0;
		
		// �}�X�N�l�擾
		uint32_t GetMask() const;

		// �R���C�_�[�`��擾
		ColliderShape GetShape() const;

		// �Փˌ��m���L�����ǂ���
		bool IsEnable() const;

		bool IsDirty() const;

	};
}