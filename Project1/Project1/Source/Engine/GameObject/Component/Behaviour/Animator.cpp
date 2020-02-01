#include "Animator.h"
#include "../../../AnimationSystem/Include.h"

namespace Engine
{
	using namespace AnimationSystem;

	std::vector<Animator::AnimatorPtr> Animator::allAnimators;

	Animator::Animator() noexcept
		: base("Animator")
		, m_avatar(nullptr)
		, m_controller(nullptr)
		, m_isPlay(false)
	{
	}

	Animator::~Animator() noexcept
	{
	}

	void Animator::SetAvatar(TargetAvatar avatar)
	{
		m_avatar = avatar;
	}

	void Animator::SetController(ControllerPtr controller)
	{
		m_controller = controller;
	}

	Animator::TargetAvatar Animator::GetAvatar() const
	{
		return m_avatar;
	}

	Animator::ControllerPtr Animator::GetController()
	{
		return m_controller;
	}

	void Animator::Play(const std::string& stateName, int32_t layerIndex, float normalizedTime)
	{
		// 0ÇÊÇËè¨Ç≥Ç¢Å‡-1Ç»ÇÁç≈èâÇÃÉåÉCÉÑÅ[
		if (layerIndex < 0)
			layerIndex = 0;
		auto layer = m_controller->GetLayer(layerIndex);
		m_isPlay = layer->Play(stateName);
	}

	void Animator::Play(int32_t stateNameHash, int32_t layerIndex, float normalizedTime)
	{
		auto layer = m_controller->GetLayer(layerIndex);
		m_isPlay = layer->Play(stateNameHash);
	}

	bool Animator::IsPlay() const
	{
		return m_isPlay;
	}

	void Animator::Update(float deltaTime)
	{
		if (!m_isPlay)
			return;
		if (m_controller)
			m_controller->Update(m_avatar, deltaTime);
	}

}