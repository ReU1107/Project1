#pragma once
#include "../../Utility/AccessObject.h"
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		// 前方宣言
		class Avatar;
		class AvatarMask;

		// モーション基底クラス
		class Motion : public AccessObject<Motion>
		{
		private:
			using base = AccessObject<Motion>;
		protected:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
		public:
			// コンストラクタ
			Motion(const std::string& name) noexcept;
			// デストラクタ
			virtual ~Motion() noexcept;
		public:
			// インスタンスID
			static const InstanceID ID() { return InstanceID::Motion; }

			// インスタンスID取得
			virtual InstanceID GetInstanceID() const override { return InstanceID::Motion; }

		public:

			// 更新
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f) = 0;

		};
	}
}