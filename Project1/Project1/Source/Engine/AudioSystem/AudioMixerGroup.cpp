#include "AudioMixerGroup.h"
#include "DXA2.h"
#include "DXA2/DXA2Device.h"
#include "AudioSubMixerData.h"

namespace Engine 
{

	namespace AudioSystem 
	{
		AudioMixerGroup::AudioMixerGroup(const std::string& name)
			: base(name)
			, m_subMixer(nullptr)
		{
		}

		AudioMixerGroup::~AudioMixerGroup()
		{
			delete m_subMixer;
		}

		AudioMixerGroup::AudioMixerGroupPtr AudioMixerGroup::Create(const std::string& name)
		{
			auto group = std::make_shared<AudioMixerGroup>(name);
			AudioSubMixerData data = {};
			group->m_subMixer = GetDevice()->CreateSubMixer(data);

			return group;
		}

		void AudioMixerGroup::AddAudioClip(AudioClipPtr clip)
		{
			m_clips.push_back(clip);
		}

	}

}