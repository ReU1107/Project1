#pragma once
#include "Collider.h"
#include "../../../Math/Matrix4x4.h"

// Transform�̎p���Ɉˑ�����
namespace Engine
{

	// ���^�R���C�_�[(�Փˑ��u)
	class BoxCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		Vector3 m_localCenter;	// ���S���W(���[�J��)
		Vector3 m_localSize;	// �T�C�Y(���[�J��)
	public:
		// �R���X�g���N�^
		BoxCollider() noexcept;
		// �f�X�g���N�^
		virtual ~BoxCollider() noexcept;

	public:
		// ���S���W(���[�J��)�ݒ�
		void SetLocalCenter(const Vector3& center);
		// �T�C�Y(���[�J��)�ݒ�
		void SetLocalSize(const Vector3& size);

		// 
		Vector3 GetHalfExtents() const;

		virtual void CalculateAABB() const override;
	};

	template<>
	inline std::shared_ptr<BoxCollider> Component::Create()
	{
		auto collider = std::make_shared<BoxCollider>();

		Collider::allColliders.push_back(collider);

		return collider;
	}
}