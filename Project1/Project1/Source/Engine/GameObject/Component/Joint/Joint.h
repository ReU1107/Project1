#pragma once
#include "../Component.h"
#include <vector>
#include "../../../Math/Vector3.h"

class btGeneric6DofSpringConstraint;

namespace Engine
{
	enum class JointType : uint8_t
	{
		Spring,		// ばね
		Hinge,		// ヒンジ(ドア等)
	};

	// 関節
	class Joint : public Component
	{
	private:
		using base = Component;
		using GameObjectPtr = std::shared_ptr<GameObject>;
		using ConnectedBones = std::vector<GameObjectPtr>;
		using JointPtr = std::shared_ptr<Joint>;
	public:
		static std::vector<JointPtr> allJoints;
	private:
		btGeneric6DofSpringConstraint* m_;
		ConnectedBones m_connectedBones;	// このオブジェクトが繋げているオブジェクト
		Vector3 m_anchorPosition;			// 

		JointType m_type;					// 
		bool m_enableCollision;
	public:
		// コンストラクタ
		Joint(const std::string& name, JointType type) noexcept;
		// デストラクタ
		virtual ~Joint() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Joint; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID()const override { return InstanceID::Joint; }

	public:
		// アンカー位置設定
		void SetAnchorPosition(const Vector3& anchor);

		// 接続オブジェクト追加
		void AddConnectBone(GameObjectPtr bone);

		// ジョイントの種類取得
		JointType GetType() const;
	};
}