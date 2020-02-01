#pragma once
#include "../Component.h"
#include "../../../Math/Include.h"

// キーポーズ行列はトランスフォームの値を考慮したもの

namespace Engine
{
	enum class BoneType : uint8_t
	{
		ForwardKinematics,	// 
		InverseKinematics,	// 
	};

	// ボーンクラス
	class Bone : public Component
	{
	private:
		using base = Component;

	private:
		Vector3 m_keyPosePosition;				// 移動
		Vector4 m_keyPoseRotation;				// 回転
		Vector3 m_fixedAxis;					// 固定軸(回転の軸を固定)
		Matrix4x4 m_offsetMatrix;				// オフセット行列
		mutable Matrix4x4 m_keyPoseLocalMatrix;	// 行列
		mutable Matrix4x4 m_keyPoseWorldMatrix;	// 行列
		mutable bool m_keyPoseIsDirty;			// ダーティフラグ
		BoneType m_type;
	public:
		// コンストラクタ
		Bone(const std::string& name, BoneType type) noexcept;
		// デストラクタ
		virtual ~Bone() noexcept;

		virtual void* GetPropertyAddress(const std::string& name) override;

		// インスタンスID
		static const InstanceID ID() { return InstanceID::Bone; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Bone; }

		// オフセット行列設定
		void SetOffsetMatrix(const Matrix4x4& offset);

		// 固定軸設定
		void SetFixedAxis(const Vector3& axis);

		// 
		void Reset();

		// ローカル空間での回転
		void LocalRotate(const Vector3& euler);
		void LocalRotate(const Vector3& axis, float angle);
		void LocalRotate(const Vector4& rotation);
		void LocalRotate(const Matrix4x4& mat);


	public:
		// オフセット行列取得
		const Matrix4x4& GetOffsetMatrix() const;
		// キーポーズ行列取得
		const Matrix4x4& GetKeyPoseMatrix() const;

		// アニメーション適用後の位置取得
		Vector3 GetWorldPosition() const;

		BoneType GetType() const;

	private:
		void CalculateMatrix() const;
	};

}
