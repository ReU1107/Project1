#pragma once
#include <functional>

namespace Engine
{
	namespace AnimationSystem
	{
		// 前方宣言
		class AnimationState;

		/*
		書き換えの必要あり
		*/

		// アニメーションイベント基底クラス
		class AnimationEvent
		{
		private:
			using Process = std::function<void(float deltaTime)>;
		private:
			AnimationState* m_state;	// 関連するアニメーション
			Process m_process;
		public:
			// コンストラクタ
			AnimationEvent() noexcept;
			// デストラクタ
			~AnimationEvent() noexcept;
		public:
			void SetAnimationState(AnimationState* state);

			// 実行
			void Execute(float deltaTime);
		};
	}
}