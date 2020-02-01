#include "DXA2Device.h"
#include <xaudio2.h>
#include <cstdint>
#include <memory>
#include <cassert>
#include "DXA2AudioVoice.h"
#include "DXA2AudioSubMixer.h"
#include "DXA2AudioEffect.h"
#include "../AudioVoiceData.h"
#include "../AudioSubMixerData.h"
#include "../AudioEffectData.h"
#include "../Enumerations/DigitalFormat.h"

#pragma comment(lib,"xaudio2.lib")

namespace Engine
{

	namespace AudioSystem 
	{

		DXA2Device::DXA2Device()
			: m_device(nullptr)
			, m_masteringVoice(nullptr)
		{
			if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) 
			{
				assert(!"COMの初期化に失敗しました");
			}
			uint32_t flag = 0;
#if _DEBUG
			//flag |= XAUDIO2_DEBUG_ENGINE;
#endif

			HRESULT hr = XAudio2Create(&m_device, flag);
#if _DEBUG
			XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
			debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
			debug.BreakMask = XAUDIO2_LOG_ERRORS;
			m_device->SetDebugConfiguration(&debug, 0);
#endif
			m_device->CreateMasteringVoice(&m_masteringVoice);

		}

		DXA2Device::~DXA2Device()
		{
			CoUninitialize();
		}
		
		void DXA2Device::Start()
		{
			m_device->StartEngine();
		}

		void DXA2Device::Stop()
		{
			m_device->StopEngine();
		}

		IAudioMaster* DXA2Device::CreateMaster(const AudioMasterData& data)
		{
			return nullptr;
		}

		IAudioVoice* DXA2Device::CreateVoice(const AudioVoiceData& data)
		{
			DXA2AudioVoice* voice = new DXA2AudioVoice();
			uint16_t tag = data.format == DigitalFormat::PCM ? 1 : 0;
			WAVEFORMATEX format = {};
			format.wFormatTag = tag;
			format.nChannels = data.channelCount;
			format.nSamplesPerSec = data.frequency;
			format.nBlockAlign = (data.bitDepth / 8) * data.channelCount;
			format.wBitsPerSample = data.bitDepth;
			format.nAvgBytesPerSec = data.frequency * format.nBlockAlign;

			uint32_t flags = 0;
			if (data.useFilter) 
			{
				flags |= XAUDIO2_VOICE_USEFILTER;
			}
			if (data.pitchShift) {
				flags |= XAUDIO2_VOICE_NOPITCH;
			}
			if (data.sampleConversion)
			{
				flags |= XAUDIO2_VOICE_NOSRC;
			}

			IXAudio2SourceVoice* sourceVoice = nullptr;
			
			if (FAILED(m_device->CreateSourceVoice
				( &sourceVoice
				, &format
				, flags
				, data.maxRatio
				, voice))) 
			{
				assert(!"ソースボイスの作成に失敗しました");
				return nullptr;
			}
			
			voice->m_nativeVoice = sourceVoice;

			return voice;
		}

		IAudioSubMixer* DXA2Device::CreateSubMixer(const AudioSubMixerData& data)
		{
			DXA2AudioSubMixer* subMixer = new DXA2AudioSubMixer();

			IXAudio2SubmixVoice* subMixVoice = nullptr;

			if (FAILED(m_device->CreateSubmixVoice(&subMixVoice, 0, 0))) 
			{
				assert(!"サブミックスボイスの作成に失敗しました");
				return nullptr;
			}
			subMixer->m_native = subMixVoice;

			return subMixer;
		}

		IAudioEffect* DXA2Device::CreateEffect(const AudioEffectData& data)
		{
			DXA2AudioEffect* effect = new DXA2AudioEffect();

			return effect;
		}
	}
}