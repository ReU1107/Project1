#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include <iostream>
#include <memory>
#include "../../Math/Include.h"

namespace Engine
{
	class Transform final : public Component
	{
	private:
		using base = Component;
	private:
		// 計算の最適化
		mutable Matrix4x4 m_localToWorld;		// ローカル→ワールド変換行列
		mutable Matrix4x4 m_worldToLocal;		// ワールド→ローカル変換行列

		Vector4 m_localRotation;				// 回転(四元数)

		Vector3 m_localPosition;				// 位置		親からみた相対的な位置
		Vector3 m_localScale;					// スケーリング

		// ダーティパターン
		mutable bool m_localToWorldIsDirty;		// 再計算(ワールド変換行列作成に必要な数値が変わったらtrue)
	public:
		// コンストラクタ
		Transform() noexcept;
		// デストラクタ
		virtual ~Transform() noexcept;
	public:
		// インスタンスID取得
		static const InstanceID ID() { return InstanceID::Transform; }
		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Transform; }

		virtual void* GetPropertyAddress(const std::string& name) override;

	public:
		// ローカル空間内の位置設定
		void SetLocalPosition(const Vector3& position);
		void SetLocalPosition(float x, float y, float z);

		// ワールド空間内の位置設定
		void SetWorldPosition(const Vector3& position);
		void SetWorldPosition(float x, float y, float z);

		// ローカル空間内のスケール値設定
		void SetLocalScale(const Vector3& scale);
		void SetLocalScale(float x, float y, float z);

		// ローカル空間内の回転角度設定
		void SetLocalRotation(const Vector3& euler);
		void SetLocalRotation(const Vector4& rotation);

		// ワールド空間内の回転角度設定
		void SetWorldRotation(const Vector4& rotation);

		// 再計算通知
		void HasChanged(bool recurse);
	public:
		// ローカル空間内の位置取得
		Vector3 GetLocalPosition() const;
		// ワールド空間内の位置取得
		Vector3 GetWorldPosition() const;

		// ローカル空間内の回転値取得
		Vector4 GetLocalRotation() const;
		// ワールド空間内の回転値取得
		Vector4 GetWorldRotation() const;

		// ローカル→ワールド変換行列取得
		const Matrix4x4& GetLocalToWorld() const;
		// ワールド→ローカル変換行列取得(ワールド変換の逆行列)
		const Matrix4x4& GetWorldToLocal() const;

		// 値の変更があったか
		bool IsDirty() const;

	public:
		// ローカル空間での平行移動
		void LocalTranslate(const Vector3& displacement);
		// ワールド空間での平行移動
		void WorldTranslate(const Vector3& displacement);

		// ローカル空間での回転
		void LocalRotate(const Vector3& euler);
		void LocalRotate(const Vector3& axis, float angle);
		void LocalRotate(const Vector4& rotation);
		// ワールド空間での回転
		void WorldRotate(const Vector3& euler);
		void WorldRotate(const Vector3& axis, float angle);
		//void WorldRotate(const Vector4 & rotate);

		// ターゲットの方向を見るように回転
		void LookAt(const Vector3& worldPosition, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(float x, float y, float z, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(std::shared_ptr<GameObject> gameObject, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(std::shared_ptr<Transform> transform, const Vector3& worldUp = Vector3(0.0f, 1.0f, 0.0f));

		// 指定軸回転
		void RotateAround(const Vector3& point, const Vector3& axis, float radian);
	public:
		// ワールド座標系のZ軸取得
		Vector3 Forward() const;
		Vector3 Backward() const;
		// ワールド座標系のX軸取得
		Vector3 Right() const;
		Vector3 Left() const;
		// ワールド座標系のY軸取得
		Vector3 Up() const;
		Vector3 Down() const;

		// 自身のワールド空間に方向を変換取得
		Vector3 TransformDirection(const Vector3& direction);
		// 自身のワールド空間に位置を変換取得
		Vector3 TransformPoint(const Vector3& point);
		// 自身のワールド空間にベクトルを変換取得
		Vector3 TransformVector(const Vector3& vector);

		// 自身のローカル空間に方向を変換取得
		Vector3 InverseTransformDirection(const Vector3& direction);
		// 自身のローカル空間に位置を変換取得
		Vector3 InverseTransformPoint(const Vector3& point);
		// 自身のローカル空間にベクトルを変換取得
		Vector3 InverseTransformVector(const Vector3& vector);

		// 
		const Matrix4x4 GetLocalMatrix() const;
	private:

		// 計算
		void CalculateMatrix() const;

	};
}

using TransformPtr = std::shared_ptr<Engine::Transform>;