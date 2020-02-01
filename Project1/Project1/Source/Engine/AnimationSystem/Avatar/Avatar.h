#pragma once
#include "../../Object.h"
#include "../Enumerations/HumanBodyBones.h"
#include <unordered_map>

namespace Engine
{
	namespace AnimationSystem
	{
		// 前方宣言
		struct BodyPart;
		class Transform;

		class Avatar final : public Object
		{
		private:
			using base = Object;
			//using BodyParts = std::unordered_map<HumanBodyBones, BodyPart>;
			using BodyParts = std::unordered_map<std::string, BodyPart>;

		private:
			BodyParts m_bodyParts;	// パーツ配列(ヒューマノイド)
			bool m_isHuman;			// ヒューマン
		public:
			// コンストラクタ
			Avatar() noexcept;
			// デストラクタ
			virtual ~Avatar() noexcept;
		public:
			// トランスフォーム数取得
			uint32_t GetTransformCount() const;
			// トランスフォーム取得
			//Transform * GetBoneTransform(HumanBodyBones humanBoneID) const;

			BodyPart GetBodyPart(const std::string& name);

			BodyParts& GetBodyParts();
		};
	}
}

using AvatarPtr = std::shared_ptr<Engine::AnimationSystem::Avatar>;