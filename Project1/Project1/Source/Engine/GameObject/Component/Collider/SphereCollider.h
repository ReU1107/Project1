#pragma once
#include "Collider.h"

namespace Engine
{

	// ���^�R���C�_�[(�Փˑ��u)
	class SphereCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		Vector3 m_localCenter;	// 
		float m_localRadius;	// ���a
	public:
		// �R���X�g���N�^
		SphereCollider() noexcept;
		// �f�X�g���N�^
		virtual ~SphereCollider() noexcept;
	public:
		// ���S�ʒu�ݒ�
		void SetLocalCenter(const Vector3& center);
		// ���a�ݒ�
		void SetLocalRadius(float radius);

		// ���S�ʒu�擾
		const Vector3& GetLocalCenter() const;

		// ���a�擾
		float GetLocalRadius() const;

		virtual void CalculateAABB() const override;

	};


	template<>
	inline std::shared_ptr<SphereCollider> Component::Create()
	{
		auto collider = std::make_shared<SphereCollider>();

		Collider::allColliders.push_back(collider);

		return collider;
	}
}