#pragma once
#include "../Component.h"
#include "../../../Math/Vector3.h"
#include "../../../PhysicsSystem/AABB.h"

namespace Engine
{

	// 前方宣言
	class RigidBody;

	namespace PhysicsSystem
	{
		class PhysicsMaterial;
	}

	// コライダーの形状
	enum class ColliderShape : uint8_t
	{
		Box,		// 箱
		Capsule,	// カプセル
		Sphere,		// 球
		Mesh,		// メッシュ
		Terrain		// 地形
	};

	struct Collision
	{
		Vector3 relativeVelocity;	// 衝突したCollider同士の相対的な速度
		// 衝突した
	};

	// コライダー(衝突装置)
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
		PhysicsMaterialPtr m_material;		// このコライダーの材質
		RigidBodyPtr m_rigidBody;			// 
		ColliderShape m_shape;
		uint32_t m_mask;
		mutable bool m_isDirty;
		bool m_enabled;
	public:
		// コンストラクタ
		Collider(const std::string& name, ColliderShape shape) noexcept;
		// デストラクタ
		virtual ~Collider() noexcept;
	public:
		// ID取得
		static const InstanceID ID() { return InstanceID::Collider; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID()const override { return InstanceID::Collider; }

	public:

		// マスク値設定
		void SetMask(uint32_t mask);

		// リジットボディ設定
		void SetRigidBody(RigidBodyPtr rigidBody);

		// リジットボディ取得
		RigidBodyPtr GetRigidBody() const;

		// マテリアル取得
		PhysicsMaterialPtr GetPhysicMaterial() const;

		// AABB取得
		const PhysicsSystem::AABB& GetAABB() const;

		virtual void CalculateAABB() const = 0;
		
		// マスク値取得
		uint32_t GetMask() const;

		// コライダー形状取得
		ColliderShape GetShape() const;

		// 衝突検知が有効かどうか
		bool IsEnable() const;

		bool IsDirty() const;

	};
}