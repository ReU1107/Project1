#include "AnimatorControllerLayer.h"
#include "../State/AnimatorStateMachine.h"
#include "../State/AnimatorStateTransition.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimatorControllerLayer::AnimatorControllerLayer(const std::string& name) noexcept
			: m_name(name)
			, m_stateMachine(nullptr)
			, m_avatarMask(nullptr)
			, m_transition(nullptr)
			, m_syncedWeight(1.0f)
			, m_syncedLayerIndex(0)
		{
			// 必ず作られるもの
			m_stateMachine = std::make_shared<AnimatorStateMachine>(name);
		}

		AnimatorControllerLayer::~AnimatorControllerLayer() noexcept
		{
		}

		AnimatorControllerLayer::ControllerLayerPtr AnimatorControllerLayer::Create(const std::string& name)
		{
			auto layer = std::make_shared<AnimatorControllerLayer>(name);
			layer->GetStateMachine()->SetOwner(layer);

			return layer;
		}

		void AnimatorControllerLayer::SetAvatarMask(AvatarMaskPtr avatarMask)
		{
			m_avatarMask = avatarMask;
		}

		void AnimatorControllerLayer::SetOverrideMotion(AnimatorStatePtr state, MotionPtr motion)
		{
		}

		void AnimatorControllerLayer::SetTransition(AnimatorStateTransitionPtr transition)
		{
			m_transition = transition;
		}

		AnimatorControllerLayer::AnimatorStateMachinePtr AnimatorControllerLayer::GetStateMachine() const
		{
			return m_stateMachine;
		}

		void AnimatorControllerLayer::AddState(AnimatorStatePtr state)
		{
			m_stateMachine->AddState(state);
		}

		bool AnimatorControllerLayer::Play(const std::string& stateName)
		{
			return m_stateMachine->Play(stateName);
		}

		bool AnimatorControllerLayer::Play(int32_t stateNameHash)
		{
			return m_stateMachine->Play(stateNameHash);
		}

		void AnimatorControllerLayer::Update(AvatarPtr avatar, float deltaTime)
		{
			// 何かしらのステート間の遷移中なら
			if (m_transition)
			{
				// 遷移が完了したら
				if (m_transition->Transition(avatar, m_avatarMask, deltaTime, m_syncedWeight))
				{
					m_transition->Reset();
					m_transition = nullptr;
				}
			}
			else 
			{
				m_stateMachine->Update(avatar, m_avatarMask, deltaTime);
			}

		}
	}
}