#pragma once
#include "../../Object.h"
#include <vector>
#include <memory>

/*
ChildAnimatorState,ChildAnimatorStateMachine
を実体で持つため
↑2つの構造体は参照カウントを変更する権利は持たない
理由:コピーを作った時に参照カウントを何度も
変更してしまう為参照カウントの管理はAnimatorStateMachineが持つ
*/

namespace Engine
{
	namespace AnimationSystem
	{
		class Avatar;
		class AvatarMask;
		class AnimatorState;
		struct ChildAnimatorState;
		struct ChildAnimatorStateMachine;
		class AnimatorStateTransition;
		class AnimatorControllerLayer;

		class AnimatorStateMachine final : public Object
		{
		private:
			using base = Object;
			using StateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using Transitions = std::vector<StateTransitionPtr>;
			using ChildStates = std::vector<ChildAnimatorState>;
			using ChildStateMachines = std::vector<ChildAnimatorStateMachine>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using ControllerLayerPtr = std::shared_ptr<AnimatorControllerLayer>;
		private:
			Transitions m_transitions;			// 全てのステートの遷移情報
			ChildStates m_states;				// ステート配列
			ChildStateMachines m_stateMachines;	// ステートマシーン配列
			StatePtr m_defaultState;			// デフォルトのステート
			StatePtr m_currentState;			// 現在再生中のステート
			ControllerLayerPtr m_owner;			// 
		public:
			// コンストラクタ
			AnimatorStateMachine(const std::string& name) noexcept;
			// デストラクタ
			virtual ~AnimatorStateMachine() noexcept;

		public:
			void SetOwner(ControllerLayerPtr layer);

			// ステート追加
			StatePtr AddState(const std::string& name);
			void AddState(StatePtr state);
			// ステートマシーン追加
			StateMachinePtr AddStateMachine(const std::string& name);
			void AddStateMachine(StateMachinePtr stateMachine);

			// ステート取得
			StatePtr GetState(uint32_t index);
			StatePtr GetState(const std::string& name);
			// 現在再生中のステート取得
			StatePtr GetCurrentState() const;

		private:
			// Childが持つAnimatorState,AnimatorStateMachineを再生する
			StatePtr SubPlay(const std::string& stateName);
			StatePtr SubPlay(int32_t stateNameHash);

		public:
			// 再生
			bool Play(const std::string& stateName);
			bool Play(int32_t stateNameHash);

			void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime);
			//// 再生しているアニメーションを更新
			//void Update();
			//// リセット
			//void Reset();
			//// ストップ
			//void Stop();
		};
	}
}

using AnimatorStateMachinePtr = std::shared_ptr<Engine::AnimationSystem::AnimatorStateMachine>;