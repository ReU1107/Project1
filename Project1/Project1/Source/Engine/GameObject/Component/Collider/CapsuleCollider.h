#pragma once
#include "Collider.h"

namespace Engine 
{
	// �J�v�Z���^�R���C�_�[(�Փˑ��u)
	class CapsuleCollider final : public Collider
	{
	private:
		using base = Collider;
	private:

		Vector3 m_localCenter;		// ���S���W(���[�J��)
		Vector3 m_localDirection;	// ����
		float m_localHeight;		// ����
		float m_localRadius;		// ���a
	public:
		// �R���X�g���N�^
		CapsuleCollider() noexcept;
		// �f�X�g���N�^
		virtual ~CapsuleCollider() noexcept;

	public:

		// ���S���W�ݒ�
		void SetLocalCenter(const Vector3& center);

		// �����ݒ�
		void SetLocalDirection(const Vector3& direction);

		// ����
		void SetLocalHeight(float height);
		// ���a
		void SetLocalRadius(float radius);

		// ���a�擾
		float GetLocalRadius() const;

		// �����擾
		float GetLocalHeight() const;

		virtual void CalculateAABB() const override;
	};

	template<>
	inline std::shared_ptr<CapsuleCollider> Component::Create()
	{
		auto collider = std::make_shared<CapsuleCollider>();

		Collider::allColliders.push_back(collider);

		return collider;
	}
}