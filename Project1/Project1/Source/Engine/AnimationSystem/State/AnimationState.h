#pragma once
#include <cstdint>
#include "../..//Utility/Timer.h"

namespace Engine
{
	class Transform;

	namespace AnimationSystem
	{
		// 前方宣言
		class AnimationClip;
		/*
		歩き状態のアニメーション このような状態を表す基本AnimationStateに一つのAnimationClip
		アニメーションブレンドをするときはどうするか今の所分かっていない
		*/
		/*
		m_isUpdate更新が必要か
		正確にはフレームindexは進んでいる
		使い方としては
		カメラに映っていないときにアニメーションをしなくていい為
		カメラに映らないと判断されたらfalse
		フレームindexは進んでいる為trueになった状態のアニメーションから適応される
		*/
		// 一つの状態のアニメーション
		class AnimationState final
		{
		private:
			AnimationClip* m_clip;		// 再生しようとしているアニメーション
			float m_speed;				// 再生速度
			uint32_t m_loopCount;		// ループ回数
			Timer m_timer;				// ローカル時間軸
			uint32_t m_frameIndex;
			bool m_isUpdate;			// 更新が必要か
		public:
			// コンストラクタ
			AnimationState() noexcept;
			// デストラクタ
			~AnimationState() noexcept;
		public:
			// アニメーションを適用するトランスフォーム追加
			void AddMixingTransform(Transform* transform, bool recursive = true);

			// アニメーションクリップ設定
			void SetAnimationClip(AnimationClip* clip);

			void SetSpeed(float speed = 1.0f);

		public:
			// 設定されたトランスフォームを削除
			void RemoveMixingTransform(Transform* transform);

			//private:
			//	// FK処理
			//	void ForwardKinematics(GameObject * gameObject);
			//
			//	// IK処理
			//	void InverseKinematics(GameObject * gameObject);
			//
		public:
			void Play();

			void Update(float deltaTime);

			void Stop();
		};
	}
}