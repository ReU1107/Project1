#pragma once
#include "IAudioComponent.h"
#include <functional>

/*
PCM(パルス符号変調)
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// 前方宣言
		class IAudioBuffer;
		class IAudioSubMixer;
		class IAudioMixerGroup;

		struct AudioBufferDesc
		{
			void* data;						// データ
			uint32_t sampleCount;			// サンプルカウント
			uint32_t startPosition;			// 開始位置
			uint32_t playLength;			// 再生する長さ
			uint32_t loopStartPosition;		// ループ開始位置
			uint32_t loopLength;			// ループする長さ
			uint32_t loopCount;				// ループ回数
		};

		// 音情報
		class __declspec(uuid("5CB8B981-A3A4-4E3F-B6CC-F5E5BAA8C325")) IAudioVoice : public IAudioComponent
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioVoice() {}

			// 再生開始
			virtual void Start() = 0;
			// 再生一時停止
			virtual void Pause() = 0;
			// 再生完全停止
			virtual void Stop() = 0;

			// ボリューム設定
			virtual void SetVolume(float volume) = 0;

			// PCMデータ供給
			virtual void SubmitBuffer(const AudioBufferDesc& buffer) = 0;

			// グループ設定
			virtual void SetGroups(IAudioSubMixer* groups[], uint32_t count) = 0;

			// エフェクト有効か
			virtual void EnableEffect(int32_t index) = 0;
			// エフェクト無効化
			virtual void DisableEffect(int32_t index) = 0;

			// 再生中のバッファが終了時に呼ばれる関数設定
			virtual void SetBufferEndFunction(const std::function<void()>& function) = 0;

		};

	}

}