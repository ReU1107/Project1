#include "Animation.h"
#include "../Transform.h"
#include "../../GameObject.h"
#include "../../../AnimationSystem/AnimationState.h"
#include "../../../AnimationSystem/AnimationClip.h"

namespace Engine
{

	Animation::Animation() noexcept
		: base("Animation")
		, m_defaultClip(nullptr)
		, m_playingState(nullptr)
		, m_isPlaying(false)
	{
	}

	Animation::~Animation() noexcept
	{
		//delete m_defaultClip;
		m_states.clear();
	}

	AnimationState* Animation::AddClip(const std::string& name, Motion* clip)
	{
		return AddClip(name, dynamic_cast<AnimationClip*>(clip));
	}

	AnimationState* Animation::AddClip(const std::string& name, AnimationClip* clip)
	{
		AnimationState* state = new AnimationState();
		state->AddMixingGameObject(GetOwner());
		state->SetAnimationClip(clip);
		m_states.insert({ name,state });
		return state;
	}

	void Animation::RemoveClip(const std::string& name)
	{
		/*auto it = m_clips.find(name);
		if (it == m_clips.cend()) {
			return;
		}
		m_clips.erase(it);*/
	}

	void Animation::Play(const std::string& name)
	{
		auto it = m_states.find(name);
		if (it == m_states.cend()) {
			return;
		}
		m_isPlaying = true;
		AnimationState* state = (*it).second;
		m_playingState = state;
		state->Play();
	}

	void Animation::Stop(const std::string& name)
	{
		auto it = m_states.find(name);
		if (it == m_states.cend()) {
			return;
		}
		m_isPlaying = false;
		AnimationState* state = (*it).second;
		m_playingState = nullptr;
		state->Stop();
	}

	AnimationState* Animation::GetState(const std::string& name)
	{
		auto it = m_states.find(name);
		if (it == m_states.cend()) {
			return nullptr;
		}

		return (*it).second;
	}

	AnimationState* Animation::GetPlayingState() const
	{
		return m_playingState;
	}

	void Animation::Update(float deltaTime)
	{
		if (!m_isPlaying) {
			return;
		}
		m_playingState->Update(deltaTime);
	}
}