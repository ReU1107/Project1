#pragma once
#include "Bone.h"
#include "../../../Math/Vector3.h"

namespace Engine
{
	// Inverse Kinematics (逆運動学)

	struct IKLink
	{
		std::shared_ptr<Bone> bone;
		Vector3 lowerLimitAngle;		// 制限角度
		Vector3 upperLimitAngle;		// 制限角度
		bool isLimit;
	};


	class IKBone : public Bone
	{
	private:
		using base = Bone;
		using BonePtr = std::shared_ptr<Bone>;
		using Links = std::vector<IKLink>;
	private:
		BonePtr m_effectorBone;			// このボーンを動かす
		Links m_links;					// リンク配列
		uint32_t m_iterationCount;		// 一回の処理でできるループ最大数
		float m_iterationLimitAngle;	// 
	public:
		// コンストラクタ
		IKBone();
		// デストラクタ
		virtual ~IKBone();

	public:
		// エフェクターボーン設定
		void SetEffectorBone(BonePtr bone);

		// リンク追加
		void AddLink(const IKLink& link);

		void SetIterationCount(uint32_t count);

		void SetIterationLimitAngle(float angle);

		BonePtr GetEffectorBone() const;

		uint32_t GetIterationCount() const;

		float GetIterationLimitAngle() const;

		const Links& GetLinks() const;

	};

}
