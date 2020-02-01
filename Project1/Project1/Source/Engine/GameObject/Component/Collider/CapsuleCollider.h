#pragma once
#include "Collider.h"

namespace Engine 
{
	// カプセル型コライダー(衝突装置)
	class CapsuleCollider final : public Collider
	{
	private:
		using base = Collider;
	private:

		Vector3 m_localCenter;		// 中心座標(ローカル)
		Vector3 m_localDirection;	// 向き
		float m_localHeight;		// 高さ
		float m_localRadius;		// 半径
	public:
		// コンストラクタ
		CapsuleCollider() noexcept;
		// デストラクタ
		virtual ~CapsuleCollider() noexcept;

	public:

		// 中心座標設定
		void SetLocalCenter(const Vector3& center);

		// 方向設定
		void SetLocalDirection(const Vector3& direction);

		// 高さ
		void SetLocalHeight(float height);
		// 半径
		void SetLocalRadius(float radius);

		// 半径取得
		float GetLocalRadius() const;

		// 高さ取得
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