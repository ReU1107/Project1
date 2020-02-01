#include "AudioClip.h"
#include "Interface/IAudioVoice.h"
#include "Enumerations/AudioClipLoadType.h"
#include "Enumerations/AudioDataLoadState.h"
#include "Enumerations/AudioEventID.h"
#include "AudioBuffer.h"
#include "AudioMixerGroup.h"
#include "AudioVoiceData.h"
#include "../Utility/EnumOperator.h"
#include "DXA2.h"
#include "DXA2/DXA2Device.h"

namespace Engine 
{
	namespace AudioSystem
	{

		AudioClip::AudioClip(const std::string& name)
			: base(name)
			, m_voice(nullptr)
			, m_frequency(0)
			, m_divisionCount(0)
			, m_currentIndex(0)
			, m_effectLayout()
			, m_channelCount(0)
			, m_bufferSize(0)
			, m_bitDepth(0)
			, m_loadType(AudioClipLoadType::DecompressOnLoad)
			, m_loadState(AudioDataLoadState::Unloaded)
			, m_state(State::Stop)
			, CallBack(nullptr)
		{
		}

		AudioClip::~AudioClip()
		{
			delete m_voice;
		}

		AudioClip::AudioClipPtr AudioSystem::AudioClip::Create(const std::string& name, uint32_t frequency, uint32_t channelCount, uint32_t bitDepth, uint32_t bufferSize, uint32_t divisionCount, DigitalFormat format)
		{
			auto clip = std::make_shared<AudioClip>(name);

			AudioVoiceData voiceData;
			voiceData.format = format;
			voiceData.bitDepth = bitDepth;
			voiceData.frequency = frequency;
			voiceData.channelCount = channelCount;

			clip->m_voice = GetDevice()->CreateVoice(voiceData);

			clip->m_divisionCount = divisionCount;
			clip->m_bufferSize = bufferSize;
			clip->m_bitDepth = bitDepth;
			clip->m_channelCount = channelCount;
			clip->m_frequency = frequency;

			uint32_t size = bufferSize / divisionCount;

			for (uint32_t i = 0; i < MaxBufferCount; ++i)
			{
				if (bitDepth == 8)
				{
					clip->m_buffers[i] = AudioBuffer::Create(PCMBitCount::Bit8, size);
				}
				else if (bitDepth == 16)
				{
					clip->m_buffers[i] = AudioBuffer::Create(PCMBitCount::Bit16, size);
				}
			}

			std::function<void()> func = std::bind(&AudioClip::BufferEnd, clip);
			clip->m_voice->SetBufferEndFunction(func);

			return clip;
		}

		uint32_t AudioClip::GetFrequency() const
		{
			return m_frequency;
		}

		uint8_t AudioClip::GetChannelCount() const
		{
			return m_channelCount;
		}

		uint8_t AudioClip::GetBitDepth() const
		{
			return m_bitDepth;
		}

		uint32_t AudioClip::GetLoadSize() const
		{
			return m_bufferSize / m_divisionCount;
		}

		void AudioSystem::AudioClip::EntryToGroup(AudioMixerGroupPtr group)
		{
			//group->AddAudioClip();
		}

		void AudioSystem::AudioClip::ExitFromGroup(AudioMixerGroupPtr group)
		{
		}

		void AudioSystem::AudioClip::BufferEnd()
		{
			// コールバック関数があるなら実行する
			if (CallBack)
				CallBack();
			m_currentIndex = (m_currentIndex + 1) % MaxBufferCount;

			// 現在再生中のバッファの参照カウントをデクリメント
			auto buffer = GetCurrentBuffer();

			AudioBufferDesc desc = {};
			desc.data = buffer->GetData();
			desc.sampleCount = buffer->GetSampleCount();
			desc.loopCount = buffer->GetLoopCount();
			desc.playLength = buffer->GetPlayLength();
			desc.loopLength = 0;
			desc.startPosition = buffer->GetStartPosition();
			desc.loopStartPosition = buffer->GetLoopPosition();

			// 次のバッファを送信
			m_voice->SubmitBuffer(desc);
		}

		void AudioSystem::AudioClip::AddEffect(AudioEffectLayout layout)
		{
			m_effectLayout |= layout;
		}

		void AudioClip::Start()
		{
			if (m_state != State::Start)
			{
				auto buffer = GetCurrentBuffer();

				AudioBufferDesc desc = {};
				desc.data = buffer->GetData();
				desc.sampleCount = buffer->GetSampleCount();
				desc.loopCount = buffer->GetLoopCount();
				desc.playLength = buffer->GetPlayLength();
				desc.loopLength = 0;
				desc.startPosition = buffer->GetStartPosition();
				desc.loopStartPosition = buffer->GetLoopPosition();

				m_voice->SubmitBuffer(desc);
				m_voice->Start();
				m_state = State::Start;
			}
		}

		void AudioClip::Pause()
		{
			if (m_state != State::Pause)
			{
				m_voice->Pause();
				m_state = State::Pause;
			}
		}

		void AudioSystem::AudioClip::Restart()
		{
			if (m_state == State::Pause)
			{
				m_voice->Start();
				m_state = State::Start;
			}
		}

		void AudioClip::Stop()
		{
			if (m_state != State::Stop)
			{
				m_voice->Stop();
				m_state = State::Stop;
			}
		}

		AudioClip::AudioBufferPtr AudioClip::GetCurrentBuffer() const
		{
			return m_buffers[m_currentIndex];
		}

		AudioClip::AudioBufferPtr AudioClip::GetNextBuffer() const
		{
			uint32_t index = (m_currentIndex + 1) % MaxBufferCount;
			return m_buffers[index];
		}

	}
}

