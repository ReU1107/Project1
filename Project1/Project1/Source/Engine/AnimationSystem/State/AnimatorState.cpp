#include "AnimatorState.h"
#include "AnimatorStateTransition.h"
#include "../Motion/Motion.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimatorState::AnimatorState(const std::string& name)
			: base(name)
			, m_motion(nullptr)
			, m_cycleOffset(0.0f)
			, m_localTime(0.0f)
			, m_speed(1.0f)
			, m_currentTransition(nullptr)
			, m_state(State::Stop)
		{
		}

		AnimatorState::~AnimatorState()
		{
			m_stateTransitions.clear();
		}

		AnimatorState::StatePtr AnimatorState::Create(const std::string& name)
		{
			auto state = std::make_shared<AnimatorState>(name);
			return state;
		}

		void AnimatorState::SetMotion(MotionPtr motion)
		{
			m_motion = motion;
		}

		AnimatorState::StateTransitionPtr AnimatorState::AddTransition(StatePtr destinationState)
		{
			auto transition = std::make_shared<AnimatorStateTransition>();
			transition->SetDestinationState(destinationState);
			transition->SetSourceState(shared_from_this());
			m_stateTransitions.push_back(transition);
			return transition;
		}

		AnimatorState::StateTransitionPtr AnimatorState::AddTransition(StateMachinePtr destinationStateMachine)
		{
			auto transition = std::make_shared<AnimatorStateTransition>();
			transition->SetDestinationStateMachine(destinationStateMachine);
			m_stateTransitions.push_back(transition);
			return transition;
		}

		void AnimatorState::AddTransition(StateTransitionPtr transition)
		{
			m_stateTransitions.push_back(transition);
		}

		AnimatorState::StatePtr AnimatorState::GetSaifityState()
		{
			for (auto& transition : m_stateTransitions) 
			{
				m_currentTransition = transition;
				return transition->GetSatisfyState();
			}
			return nullptr;
		}

		void AnimatorState::Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight)
		{
			if (m_state == State::Play)
			{
				// ローカルタイムを進める
				m_localTime += (deltaTime * m_speed);
				m_motion->Update(avatar, mask, m_localTime, weight);
			}
		}

		void AnimatorState::SetSpeed(float speed)
		{
			m_speed = speed;
		}

		AnimatorState::StateTransitionPtr AnimatorState::GetCurrentTransition() const
		{
			return m_currentTransition;
		}

		void AnimatorState::Play()
		{
			m_state = State::Play;
		}

	}
}