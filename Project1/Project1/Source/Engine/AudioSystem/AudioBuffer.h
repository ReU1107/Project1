#pragma once
#include <cstdint>
#include <memory>

namespace Engine
{

	namespace AudioSystem
	{
		enum class PCMBitCount
		{
			Bit8,	// 
			Bit16,	// 
		};

		class AudioBuffer final
		{
		private:
			using AudioBufferPtr = std::shared_ptr<AudioBuffer>;

			union PCMBitStream
			{
				uint8_t* bit8;
				uint16_t* bit16;
				void* general;
			};
			PCMBitStream m_pcmBitStream;// データ配列
			PCMBitCount m_pcmBitCount;	// 1サンプルあたりのビット数
			uint32_t m_sampleCount;		// サンプル数
			uint32_t m_startPosition;	// バッファ内での開始位置   
			uint32_t m_playLength;		// バッファ内での再生範囲	
			uint32_t m_loopPosition;	// ループ開始位置
			uint32_t m_loopCount;		// ループ数

		public:
			// コンストラクタ
			AudioBuffer();
			// デストラクタ
			~AudioBuffer();
		public:
			// バッファ作成
			static AudioBufferPtr Create(PCMBitCount bitCount, uint32_t size);
			
		public:

			// 開始位置設定
			void SetStartPosition(uint32_t startPosition = 0);
			// 再生長設定
			void SetPlayLength(uint32_t playLength);
			// ループ開始位置設定
			void SetLoopPosition(uint32_t loopPosition = 0);
			// ループ数設定
			void SetLoopCount(uint32_t loopCount = 255);

			// データサイズ取得
			uint32_t GetSampleCount() const;

			// データ取得
			void* GetData() const;

			// 再生開始位置取得
			uint32_t GetStartPosition() const ;

			// 再生する長さ取得
			uint32_t GetPlayLength() const;

			// ループ開始位置取得
			uint32_t GetLoopPosition() const;

			// ループ数取得
			uint32_t GetLoopCount() const;

		};
	}
}

using AudioBufferPtr = std::shared_ptr<Engine::AudioSystem::AudioBuffer>;