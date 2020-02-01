#pragma once
#include <cstdint>

/*
オーディオの再生機能を持った
低レベルAPI,SDKにアクセスするための
デバイス
このクラスを継承して作ってください
例でXAudio2のデバイス作成済み
名前をDirectX Audio2より DXA2Device
*/

namespace Engine
{

	namespace AudioSystem 
	{

		// 前方宣言
		class IAudioMaster;
		class IAudioVoice;
		class IAudioSubMixer;
		class IAudioEffect;

		struct AudioMasterData;
		struct AudioVoiceData;
		struct AudioSubMixerData;
		struct AudioEffectData;

		/*
		オーディオ再生
		低レベルAPIアクセスデバイス
		*/
		class __declspec(uuid("71314576-7723-4EB9-8980-4393A5D8E94F")) IAudioDevice
		{
		public:
			virtual ~IAudioDevice() {}
			
			// 
			virtual void Start() = 0;

			// 
			virtual void Stop() = 0;

			// マスター作成
			virtual IAudioMaster* CreateMaster(const AudioMasterData& data) = 0;

			// ボイス作成
			virtual IAudioVoice* CreateVoice(const AudioVoiceData& data) = 0;
			// サブミキサー作成
			virtual IAudioSubMixer* CreateSubMixer(const AudioSubMixerData& data) = 0;

			// エフェクト作成
			virtual IAudioEffect* CreateEffect(const AudioEffectData& data) = 0;

		};

	}
}