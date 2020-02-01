#pragma once
#include "../Interface/IAudioDevice.h"

// 前方宣言
struct IXAudio2;
struct IXAudio2MasteringVoice;

namespace Engine
{

	namespace AudioSystem
	{

		/*
		DirectX Audio2
		XAudio2
		*/

		class DXA2Device final : public IAudioDevice
		{
		private:
			using base = IAudioDevice;
		private:
			IXAudio2* m_device;							// デバイス
			IXAudio2MasteringVoice* m_masteringVoice;	// 
		public:
			// コンストラクタ
			DXA2Device();
			// デストラクタ
			~DXA2Device();

			// 
			virtual void Start() override;

			// 
			virtual void Stop() override;

			// マスター作成
			virtual IAudioMaster* CreateMaster(const AudioMasterData& data) override;
			// ボイス作成
			virtual IAudioVoice* CreateVoice(const AudioVoiceData& data) override;
			// サブミキサー作成
			virtual IAudioSubMixer* CreateSubMixer(const AudioSubMixerData& data) override;

			// エフェクト作成
			virtual IAudioEffect* CreateEffect(const AudioEffectData& data) override;

		};

	}

}