#pragma once
#include <vector>
#include <array>
#include "../Utility/AccessObject.h"
#include "Enumerations/DigitalFormat.h"

/*
FMOD::Studio の event的な扱い
*/

/*
unity は波形データ読み込みを
自身で記述する必要がある
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		class IAudioVoice;
		class IAudioSubMixer;
		class IAudioEffect;
		class AudioBuffer;
		class AudioMixerGroup;
		class AudioLoader;

		enum class AudioEffectLayout : uint16_t;
		enum class AudioClipLoadType : uint8_t;
		enum class AudioDataLoadState : uint8_t;
		enum class AudioEventID : uint8_t;

		class AudioClip final : public AccessObject<AudioClip>
		{
		private:
			enum class State : uint8_t
			{
				Start,
				Pause,
				Stop,
			};
			static const uint32_t MaxBufferCount = 3;

			using base = AccessObject<AudioClip>;
			using AudioClipPtr = std::shared_ptr<AudioClip>;
			using AudioBufferPtr = std::shared_ptr<AudioBuffer>;
			using AudioMixerGroupPtr = std::shared_ptr<AudioMixerGroup>;
			using AudioMixerGroups = std::vector<AudioMixerGroupPtr>;
			using AudioBuffers = std::array<AudioBufferPtr, MaxBufferCount>;
		private:
			AudioMixerGroups m_groups;			// グループ配列
			AudioBuffers m_buffers;				// バッファ配列

			IAudioVoice* m_voice;				// ボイス

			uint32_t m_frequency;				// サンプル周波数

			uint32_t m_divisionCount;			// バッファ分割数
			uint32_t m_currentIndex;			// 現在処理中のバッファ番号
			uint32_t m_bufferSize;				// 

			AudioEffectLayout m_effectLayout;	// エフェクトレイアウト

			uint8_t m_channelCount;				// チャンネル数
			uint8_t m_bitDepth;					// 使用ビット数

			AudioClipLoadType m_loadType;		// 読み込み方法
			AudioDataLoadState m_loadState;		// 読み込み状況
			State m_state;
		public:
			// コンストラクタ
			AudioClip(const std::string& name);
			// デストラクタ
			virtual ~AudioClip();
		public:
			// オーディオクリップ作成
			static AudioClipPtr Create(const std::string& name, uint32_t frequency, uint32_t channelCount, uint32_t bitDepth, uint32_t bufferSize, uint32_t divisionCount = 1, DigitalFormat format = DigitalFormat::PCM);

		public:
			// グループに所属
			void EntryToGroup(AudioMixerGroupPtr group);

			// グループより脱退
			void ExitFromGroup(AudioMixerGroupPtr group);

			// バッファば
			void BufferEnd();

			// エフェクト
			void AddEffect(AudioEffectLayout layout);

			// 開始
			void Start();

			// 一時停止
			void Pause();

			// 再開始
			void Restart();

			// 完全停止
			void Stop();

		public:

			// 周波数取得
			uint32_t GetFrequency() const;
			// チャンネル数取得
			uint8_t GetChannelCount() const;
			// ビット深度取得
			uint8_t GetBitDepth() const;

			// バッファ用に読み込むサイズ取得
			uint32_t GetLoadSize() const;

			// 再生中のバッファ取得
			AudioBufferPtr GetCurrentBuffer() const;
			// 次に再生するバッファ取得
			AudioBufferPtr GetNextBuffer() const;

			std::function<void()> CallBack;
		};
	}
	
}

using AudioClipPtr = std::shared_ptr<Engine::AudioSystem::AudioClip>;