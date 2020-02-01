#pragma once
#include "../../Object.h"
#include "../Enumerations/AvatarMaskBodyPart.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class Avatar;

		class AvatarMask final : public Object
		{
		private:
			using base = Object;
			using AvatarPtr = std::shared_ptr<Avatar>;
		private:
			AvatarPtr m_baseAvatar;			// マスクしようとしているアバター
			uint32_t m_transformCount;		// トランスフォーム数
			AvatarMaskBodyPart m_maskPart;	// マスクするパーツ(ビット演算)
		public:
			// コンストラクタ
			AvatarMask(const std::string& name) noexcept;
			// デストラクタ
			virtual ~AvatarMask() noexcept;
		public:
			// アバター設定
			void SetAvatar(AvatarPtr avatar);

			// マスクパーツ追加
			void AddMaskBodyPart(AvatarMaskBodyPart part);
			// マスクされているパーツ取得
			AvatarMaskBodyPart GetMaskBodyPart();

			// アバターボーン数取得
			uint32_t GetTransformCount() const;

		};
	}
}

using AvatarMaskPtr = std::shared_ptr<Engine::AnimationSystem::AvatarMask>;