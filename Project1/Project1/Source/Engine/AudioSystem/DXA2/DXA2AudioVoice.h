#pragma once
#include "../Interface/IAudioVoice.h"
#include <xaudio2.h>

struct IXAudio2SourceVoice;

/*
コールバック処理を分ける予定
*/

namespace Engine 
{

	namespace AudioSystem 
	{

		class IAudioListener;
		enum class AudioEffectLayout : uint16_t;

		class DXA2AudioVoice final : public IAudioVoice, public IXAudio2VoiceCallback
		{
		private:
			using base = IAudioVoice;
			friend class DXA2Device;
		private:
			IXAudio2SourceVoice* m_nativeVoice;			// ボイス
			std::function<void()> m_bufferEndFunc;
		private:
			// IXAudio2VoiceCallbackインターフェースのイベントハンドラ
			void __stdcall OnBufferStart(void* pBufferContext) override;
			void __stdcall OnBufferEnd(void* pBufferContext) override;
			void __stdcall OnLoopEnd(void* pBufferContext) override;
			void __stdcall OnStreamEnd() override;
			void __stdcall OnVoiceProcessingPassStart(UINT32 BytesRequired) override;
			void __stdcall OnVoiceProcessingPassEnd() override;
			void __stdcall OnVoiceError(void* pBufferContext, HRESULT Error) override;
		public:
			// コンストラクタ
			DXA2AudioVoice();
			// デストラクタ
			~DXA2AudioVoice();

			// 低レベルAPI生ポインタ取得
			virtual void* GetNativeVoice() const override;
			// 再生開始
			virtual void Start() override;
			// 再生一時停止
			virtual void Pause() override;
			// 再生完全停止
			virtual void Stop() override;

			virtual void SetVolume(float volume) override;

			// PCM供給
			virtual void SubmitBuffer(const AudioBufferDesc& buffer) override;

			// グループ設定
			virtual void SetGroups(IAudioSubMixer* groups[], uint32_t count) override;

			// エフェクト設定
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) override;

			void SetEffects(AudioEffectLayout layout);

			// エフェクト有効化
			virtual void EnableEffect(int32_t index) override;

			// エフェクト無効化
			virtual void DisableEffect(int32_t index) override;


			virtual void SetBufferEndFunction(const std::function<void()>& function) override;

			// 
			//DeclareIUnknownInterfaces();

		};

	}

}


/*		virtual uint32_t AddRef() override;

		virtual uint32_t Release() override;

		virtual bool QueryInterface(const _GUID& guid, void** object) override;
*/