#pragma once
#include "Collider.h"
#include "../../../Math/Matrix4x4.h"

// Transformの姿勢に依存する
namespace Engine
{

	// 箱型コライダー(衝突装置)
	class BoxCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		Vector3 m_localCenter;	// 中心座標(ローカル)
		Vector3 m_localSize;	// サイズ(ローカル)
	public:
		// コンストラクタ
		BoxCollider() noexcept;
		// デストラクタ
		virtual ~BoxCollider() noexcept;

	public:
		// 中心座標(ローカル)設定
		void SetLocalCenter(const Vector3& center);
		// サイズ(ローカル)設定
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