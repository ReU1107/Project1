#include "AnimatorStateMachine.h"
#include "AnimatorState.h"
#include "ChildAnimatorState.h"
#include "ChildAnimatorStateMachine.h"
#include "AnimatorStateTransition.h"
#include "AnimatorState.h"
#include "../Controller/AnimatorControllerLayer.h"

namespace Engine
{

	namespace AnimationSystem
	{
		AnimatorStateMachine::AnimatorStateMachine(const std::string& name) noexcept
			: base(name)
			, m_defaultState(nullptr)
			, m_currentState(nullptr)
			, m_owner(nullptr)
		{
		}

		AnimatorStateMachine::~AnimatorStateMachine() noexcept
		{
			m_stateMachines.clear();
		}

		void AnimatorStateMachine::SetOwner(ControllerLayerPtr layer)
		{
			m_owner = layer;
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::AddState(const std::string& name)
		{
			auto state = std::make_shared<AnimatorState>(name);
			ChildAnimatorState child(state);
			m_states.push_back(child);

			return state;
		}

		void AnimatorStateMachine::AddState(StatePtr state)
		{
			ChildAnimatorState child(state);
			m_states.push_back(child);
		}

		AnimatorStateMachine::StateMachinePtr AnimatorStateMachine::AddStateMachine(const std::string& name)
		{
			auto stateMachine = std::make_shared<AnimatorStateMachine>(name);
			ChildAnimatorStateMachine child(stateMachine);
			m_stateMachines.push_back(child);

			return stateMachine;
		}
		void AnimatorStateMachine::AddStateMachine(StateMachinePtr stateMachine)
		{
			ChildAnimatorStateMachine child(stateMachine);
			m_stateMachines.push_back(child);
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::GetState(uint32_t index)
		{
			return m_states.at(index).state;
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::GetState(const std::string& name)
		{
			StatePtr state = nullptr;
			for (auto& child : m_states)
			{
				if (child.state->GetName() == name)
				{
					state = child.state;
					break;
				}
			}
			return state;
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::GetCurrentState() const
		{
			// 再生されていないならnullptrが返る
			return m_currentState;
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::SubPlay(const std::string& stateName)
		{
			/*
			2つ以上同時に再生しない
			もしそんな事をするときはBlendTreeのAnimatorStateを
			使用するかSyncLayerを使用する必要がある
			*/
			for (auto& child : m_states) 
			{
				StatePtr state = child.state;
				if (state->GetName() == stateName) 
				{
					return state;
				}
			}
			for (auto& child : m_stateMachines) 
			{
				StateMachinePtr stateMachine = child.stateMachine;
				StatePtr state = stateMachine->SubPlay(stateName);
				return state;
			}

			return nullptr;
		}

		AnimatorStateMachine::StatePtr AnimatorStateMachine::SubPlay(int32_t stateNameHash)
		{
			for (auto& child : m_states)
			{
				StatePtr state = child.state;
				if (state->GetNameHash() == stateNameHash)
				{
					return state;
				}
			}
			for (auto& child : m_stateMachines) 
			{
				StateMachinePtr stateMachine = child.stateMachine;
				StatePtr state = stateMachine->SubPlay(stateNameHash);
				return state;
			}
			return nullptr;
		}

		bool AnimatorStateMachine::Play(const std::string& stateName)
		{
			StatePtr state = nullptr;
			state = SubPlay(stateName);
			if (state) 
			{
				m_currentState = state;
				m_currentState->Play();
				return true;
			}
			return false;
		}

		bool AnimatorStateMachine::Play(int32_t stateNameHash)
		{
			StatePtr state = nullptr;
			state = SubPlay(stateNameHash);
			if (state) 
			{
				m_currentState = state;
				return true;
			}
			return false;
		}

		void AnimatorStateMachine::Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime)
		{
			if (!m_currentState)
				return;
			// 遷移条件をクリアしたステートがあるなら変更する
			StatePtr nextState = m_currentState->GetSaifityState();
			if (nextState)
			{
				// 遷移の情報を伝える
				m_owner->SetTransition(m_currentState->GetCurrentTransition());
				nextState->Play();
				m_currentState = nextState;
			}
			else
			{
				m_currentState->Update(avatar, mask, deltaTime);
			}
		}

	}
}