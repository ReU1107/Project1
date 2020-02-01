#include "AudioSource.h"
#include "../../../AudioSystem/AudioClip.h"

namespace Engine
{
	std::vector<AudioSource::AudioSourcePtr> AudioSource::allAudioSource;

	AudioSource::AudioSource() noexcept
		: base("AudioSource")
		, m_clip(nullptr)
		, m_is3D(false)
	{
	}

	AudioSource::~AudioSource() noexcept
	{
	}

	void AudioSource::SetClip(AudioClipPtr clip)
	{
		m_clip = clip;
	}

	AudioSource::AudioClipPtr AudioSource::GetClip() const
	{
		return m_clip;
	}

	void AudioSource::Start()
	{
		m_clip->Start();
	}
	
	void AudioSource::Pause()
	{
		m_clip->Pause();
	}

	void AudioSource::Restart()
	{
		m_clip->Restart();
	}
	
	void AudioSource::Stop()
	{
		m_clip->Stop();
	}
}