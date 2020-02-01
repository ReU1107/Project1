#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <memory>

/*
部分的なアニメーションブレンディングを行いたいときは
Synced関連の値をしようする
ブレンディングの仕方は加算ブレンディングか
*/
/*
レイヤーが動かそうとしているオブジェクトの型を持っておく
モーフィング関連ならmesh正確にはSkinnedMeshRenderer
スキニング関連ならTransform
*/

namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class AnimatorStateMachine;
		class AnimatorState;
		class AvatarMask;
		class Avatar;
		class AnimatorStateTransition;

		// レイヤー
		class AnimatorControllerLayer final
		{
		private:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using AnimatorStateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using AnimatorStatePtr = std::shared_ptr<AnimatorState>;
			using AnimatorStateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using ControllerLayerPtr = std::shared_ptr<AnimatorControllerLayer>;
		private:
			std::string m_name;						// レイヤー名
			AnimatorStateMachinePtr m_stateMachine;	// ステートマシーン
			AvatarMaskPtr m_avatarMask;				// アバターマスク
			AnimatorStateTransitionPtr m_transition;// 
			int32_t m_syncedLayerIndex;				// 同期するレイヤー番号
			float m_syncedWeight;					// 同期の度合い

		public:
			// コンストラクタ
			AnimatorControllerLayer(const std::string& name) noexcept;
			// デストラクタ
			~AnimatorControllerLayer() noexcept;

			static ControllerLayerPtr Create(const std::string& name);
			
		public:
			// アバターマスク設定
			void SetAvatarMask(AvatarMaskPtr avatarMask);
			// 
			void SetOverrideMotion(AnimatorStatePtr state, MotionPtr motion);

			void SetTransition(AnimatorStateTransitionPtr transition);

			// ステートマシーン取得
			AnimatorStateMachinePtr GetStateMachine() const;

			// ステート追加
			void AddState(AnimatorStatePtr state);

			// 再生
			bool Play(const std::string& stateName);
			bool Play(int32_t stateNameHash);

			// レイヤー更新
			void Update(AvatarPtr avatar, float deltaTime);
		};
	}
}

using AnimatorControllerLayerPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorControllerLayer>;