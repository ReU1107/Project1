#include "AnimatorStateTransition.h"
#include "AnimatorCondition.h"
#include "AnimatorState.h"
#include "AnimatorStateMachine.h"

namespace Engine
{
	namespace AnimationSystem
	{

		AnimatorStateTransition::AnimatorStateTransition() noexcept
			: base("AnimatorStateTransition")
			, m_sourceState(nullptr)
			, m_destinationState(nullptr)
			, m_stateMachine(nullptr)
			, m_transitionTime(1.0f)
			, m_localTime(0.0f)
		{
		}

		AnimatorStateTransition::~AnimatorStateTransition() noexcept
		{
		}

		void AnimatorStateTransition::AddCondition(const AnimatorCondition& condition)
		{
			m_conditions.push_back(condition);
		}

		void AnimatorStateTransition::SetSourceState(StatePtr state)
		{
			m_sourceState = state;
		}

		void AnimatorStateTransition::SetDestinationState(StatePtr state)
		{
			m_destinationState = state;
		}

		void AnimatorStateTransition::SetDestinationStateMachine(StateMachinePtr stateMachine)
		{
			m_stateMachine = stateMachine;
		}

		void AnimatorStateTransition::SetTransitionTime(float transitionTime)
		{
			m_transitionTime = transitionTime;
		}

		AnimatorStateTransition::StatePtr AnimatorStateTransition::GetDestinationState() const
		{
			return m_destinationState;
		}

		AnimatorStateTransition::StateMachinePtr AnimatorStateTransition::GetDestinationStateMachine() const
		{
			return m_stateMachine;
		}

		bool AnimatorStateTransition::Transition(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight)
		{
			m_localTime += deltaTime;

			if (m_localTime >= m_transitionTime)
			{
				return true;
			}

			float preWeight = ((m_localTime - 0.0f) / (m_transitionTime - 0.0f));
			float postWeight = 1.0f - preWeight;

			m_sourceState->Update(avatar, mask, deltaTime, preWeight * weight);

			m_destinationState->Update(avatar, mask, deltaTime, postWeight * weight);

			return false;
		}

		void AnimatorStateTransition::Reset()
		{
			m_localTime = 0.0f;
		}

		AnimatorStateTransition::StatePtr AnimatorStateTransition::GetSatisfyState()
		{
			/*
			condition‚ª‚ÂğŒ‚ğ‘S‚Ä–‚½‚µ‚½‚ç
			destinationState‚ğ•Ô‚·
			àˆê‚Â‚Å‚à–‚½‚µ‚Ä‚È‚¢‚È‚ç
			nullptr
			*/
			for (auto& condition : m_conditions)
			{
				if (!condition.Compare())
					return nullptr;
			}
			return m_destinationState;
		}
	}
}