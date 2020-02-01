#include "DXA2AudioVoice.h"
#include "DXA2AudioEffect.h"
#include "DXA2AudioSubMixer.h"
#include "../Enumerations/AudioEffectLayout.h"
#include "../Interface/IAudioListener.h"
#include "../../Utility/EnumOperator.h"
#include <xaudio2.h>
#include <xapo.h>

namespace Engine 
{

	namespace AudioSystem
	{
		DXA2AudioVoice::DXA2AudioVoice()
			//: base()
			: m_nativeVoice(nullptr)
		{
		}

		DXA2AudioVoice::~DXA2AudioVoice()
		{
			m_nativeVoice->DestroyVoice();
		}

		//uint32_t DXA2AudioVoice::AddRef()
		//{
		//	return ++m_referenceCount;
		//}

		//uint32_t DXA2AudioVoice::Release()
		//{
		//	if (--m_referenceCount <= 0) {
		//		delete this;
		//		return 0;
		//	}
		//	return m_referenceCount;
		//}

		void* DXA2AudioVoice::GetNativeVoice() const
		{
			return m_nativeVoice;
		}

		void DXA2AudioVoice::Start()
		{
			m_nativeVoice->Start();
		}

		void DXA2AudioVoice::Pause()
		{
			m_nativeVoice->Stop();
		}

		void DXA2AudioVoice::Stop()
		{
			m_nativeVoice->Stop();
			// サブミット済みバッファを削除
			m_nativeVoice->FlushSourceBuffers();
		}

		void DXA2AudioVoice::SetVolume(float volume)
		{
			m_nativeVoice->SetVolume(volume);
		}

		void DXA2AudioVoice::SubmitBuffer(const AudioBufferDesc& buffer)
		{
			XAUDIO2_BUFFER submitBuffer = {};
			submitBuffer.pAudioData = (uint8_t*)buffer.data;
			submitBuffer.AudioBytes = buffer.sampleCount;
			submitBuffer.PlayBegin = buffer.startPosition;
			submitBuffer.PlayLength = buffer.playLength;
			submitBuffer.LoopBegin = buffer.loopStartPosition;
			submitBuffer.LoopLength = buffer.loopLength;
			submitBuffer.LoopCount = buffer.loopCount;
			//XAUDIO2_MAX_BUFFER_BYTES
			auto hr = m_nativeVoice->SubmitSourceBuffer(&submitBuffer);
			if (FAILED(hr))
			{
				assert(!"バッファ送信に失敗しました");
			}

		}

		static const int MAXGroup = 2;

		void DXA2AudioVoice::SetGroups(IAudioSubMixer* groups[], uint32_t count)
		{
			XAUDIO2_SEND_DESCRIPTOR descriptor[MAXGroup] = {};
		
			for (uint32_t i = 0; i < count; ++i) 
			{
				descriptor[i].pOutputVoice = (IXAudio2Voice*)groups[i]->GetNativeVoice();
				descriptor[i].Flags = 0;
			}
			
			XAUDIO2_VOICE_SENDS sends = {};
			sends.SendCount = count;
			m_nativeVoice->SetOutputVoices(&sends);
		}

		void DXA2AudioVoice::SetEffects(IAudioEffect* effects[], uint32_t count)
		{
			XAUDIO2_EFFECT_DESCRIPTOR descriptor[2];
			for (uint32_t i = 0; i < count; ++i) 
			{
				descriptor[i].OutputChannels = 0;
				descriptor[i].pEffect = (IXAPO*)effects[i]->GetNativeEffect();
			}
			XAUDIO2_EFFECT_CHAIN chain = {};
			chain.EffectCount = count;
			chain.pEffectDescriptors = descriptor;

	//		m_nativeVoice->SetFilterParameters();

			m_nativeVoice->SetEffectChain(&chain);
		}

		void DXA2AudioVoice::SetEffects(AudioEffectLayout layout)
		{
			if ((layout & AudioEffectLayout::LowPassFilter) != 0) 
			{

				XAUDIO2_FILTER_PARAMETERS parameters = {};
				parameters.Type = LowPassFilter;
				parameters.Frequency = 0.0f;
				parameters.OneOverQ = 0.0f;
				m_nativeVoice->SetFilterParameters(&parameters);
			}

		}

		void DXA2AudioVoice::EnableEffect(int32_t index)
		{
			m_nativeVoice->EnableEffect(index);
		}

		void DXA2AudioVoice::DisableEffect(int32_t index)
		{
			m_nativeVoice->DisableEffect(index);
		}

		void DXA2AudioVoice::SetBufferEndFunction(const std::function<void()>& function)
		{
			m_bufferEndFunc = function;
		}
		
		void __stdcall DXA2AudioVoice::OnBufferStart(void* pBufferContext)
		{
			//MessageBox(nullptr, "バッファが開始", "", MB_OK);
			OutputDebugString("バッファ開始しました");
		}
		
		void __stdcall DXA2AudioVoice::OnBufferEnd(void* pBufferContext)
		{
			if (m_bufferEndFunc)
				m_bufferEndFunc();
			//MessageBox(nullptr, "バッファが無くなりました", "", MB_OK);
			OutputDebugString("バッファが無くなりました");
		}

		void __stdcall DXA2AudioVoice::OnLoopEnd(void* pBufferContext)
		{
			//MessageBox(nullptr, "ループ", "", MB_OK);
			OutputDebugString("ループが終わりました");
		}
		
		void __stdcall DXA2AudioVoice::OnStreamEnd()
		{
			//MessageBox(nullptr, "わからない", "", MB_OK);
			OutputDebugString("ストリーミング？が終わりました");
		}
		
		void __stdcall DXA2AudioVoice::OnVoiceProcessingPassStart(UINT32 BytesRequired)
		{
			//MessageBox(nullptr, L"わからない2", L"", MB_OK);
			OutputDebugString("プロセス");
		}
		
		void __stdcall DXA2AudioVoice::OnVoiceProcessingPassEnd()
		{
			//MessageBox(nullptr, L"わからない3", L"", MB_OK);
			OutputDebugString("ボイス処理が終わりました");
		}
		
		void __stdcall DXA2AudioVoice::OnVoiceError(void* pBufferContext, HRESULT Error)
		{
			//MessageBox(nullptr, "エラー", "", MB_OK);
			OutputDebugString("ボイスエラーが発生しました");
		}
	}
}