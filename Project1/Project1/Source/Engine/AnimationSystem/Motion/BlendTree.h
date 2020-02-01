#pragma once
#include "Motion.h"
#include "../Enumerations/BlendTreeType.h"
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{
		/*
		2つ以上のアニメーションをブレンドする際に使用する
		このクラスを使用してできるモーションは
		ランタイム時につくられるもの
		*/
		struct ChildMotion;

		class BlendTree final : public Motion
		{
		private:
			using base = Motion;
			using ChildMotions = std::vector<ChildMotion>;
			using MotionPtr = std::shared_ptr<Motion>;
		private:
			ChildMotions m_childMotions;
			BlendTreeType m_type;	// ブレンドアルゴリズム
			bool m_isActive;
		public:
			BlendTree(const std::string& name) noexcept;
			virtual ~BlendTree() noexcept;
		private:
			// 一次元Lerpブレンディング
			void OneDimensionLerp();
		public:
			bool IsActive() const { return m_isActive; }

			void Active(bool active = true) { m_isActive = active; }

			void Clear();

			// 子モーション追加
			void AddChild(MotionPtr motion);
			void AddChild(const ChildMotion& child);

			// 子モーション削除
			void RemoveChild(uint32_t index);

			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f) override;
		};
	}
}
