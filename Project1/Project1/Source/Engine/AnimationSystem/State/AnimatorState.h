#pragma once
#include "../../Object.h"
#include <vector>
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class Avatar;
		class AvatarMask;
		class AnimatorStateTransition;
		class AnimatorStateMachine;

		class AnimatorState final : public std::enable_shared_from_this<AnimatorState>, public Object
		{
		private:
			using base = Object;
			using StateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using StateTransitions = std::vector<StateTransitionPtr>;

			enum class State : uint8_t
			{
				Stop,
				Play,
			};
		private:
			StateTransitions m_stateTransitions;		// 遷移配列
			MotionPtr m_motion;							// このステートに割り振られたモーション
			float m_cycleOffset;						// オフセット
			float m_localTime;							// ローカル時間
			float m_speed;								// 再生速度(単位:秒)デフォルト1.0s
			StateTransitionPtr m_currentTransition;		// 
			State m_state;								// 状態
		public:
			// コンストラクタ
			AnimatorState(const std::string& name);
			// デストラクタ
			virtual ~AnimatorState();

			static StatePtr Create(const std::string& name);
		public:
			// モーション設定
			void SetMotion(MotionPtr motion);

			// ステートマシーンビヘイビア追加
			template<class T>
			inline T* AddStateMachineBehaviour();

			// 遷移先追加
			StateTransitionPtr AddTransition(StatePtr destinationState);
			StateTransitionPtr AddTransition(StateMachinePtr destinationStateMachine);
			void AddTransition(StateTransitionPtr transition);

			StatePtr GetSaifityState();

			void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f);

			// スピード設定
			void SetSpeed(float speed = 1.0f);

			StateTransitionPtr GetCurrentTransition() const;

			// 再生
			void Play();
			// リセット
			void Reset();
			// ストップ
			void Stop();

		};

		template<class T>
		inline T* AnimatorState::AddStateMachineBehaviour()
		{
			return nullptr;
		}
	}
}

using AnimatorStatePtr = std::shared_ptr<Engine::AnimationSystem::AnimatorState>;