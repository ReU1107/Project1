#pragma once
#include "../../Object.h"
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{

		struct AnimatorCondition;
		class AnimatorState;
		class AnimatorStateMachine;
		class Avatar;
		class AvatarMask;

		// アニメーション遷移基底クラス
		class AnimatorStateTransition : public Object
		{
		private:
			using base = Object;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using Conditions = std::vector<AnimatorCondition>;

		private:
			Conditions m_conditions;			// 遷移条件配列
			StatePtr m_sourceState;				// 遷移元のステート
			StatePtr m_destinationState;		// 遷移先のステート
			StateMachinePtr m_stateMachine;		// 
			float m_transitionTime;				// 何秒かけて遷移するか
			float m_localTime;					// ローカルタイム

		public:
			// コンストラクタ
			AnimatorStateTransition() noexcept;
			// 仮想デストラクタ
			virtual ~AnimatorStateTransition() noexcept;

		public:
			// 遷移条件追加
			void AddCondition(const AnimatorCondition& condition);

			// 遷移元のステート設定
			void SetSourceState(StatePtr state);

			// 遷移先のステート設定
			void SetDestinationState(StatePtr state);

			// 遷移先のステートマシーン設定
			void SetDestinationStateMachine(StateMachinePtr stateMachine);

			void SetTransitionTime(float transitionTime);

			// 遷移先のステート取得
			StatePtr GetDestinationState() const;

			// 遷移先のステートマシーン取得
			StateMachinePtr GetDestinationStateMachine() const;

			// 遷移処理
			bool Transition(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f);

			// リセット処理
			void Reset();

			// 条件を満たした
			StatePtr GetSatisfyState();

		};
	}
}

using AnimatorStateTransitionPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorStateTransition>;