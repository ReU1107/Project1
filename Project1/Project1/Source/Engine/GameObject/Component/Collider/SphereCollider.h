#pragma once
#include "Collider.h"

namespace Engine
{

	// 球型コライダー(衝突装置)
	class SphereCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		Vector3 m_localCenter;	// 
		float m_localRadius;	// 半径
	public:
		// コンストラクタ
		SphereCollider() noexcept;
		// デストラクタ
		virtual ~SphereCollider() noexcept;
	public:
		// 中心位置設定
		void SetLocalCenter(const Vector3& center);
		// 半径設定
		void SetLocalRadius(float radius);

		// 中心位置取得
		const Vector3& GetLocalCenter() const;

		// 半径取得
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