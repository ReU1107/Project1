#pragma once
#include "../Engine/AudioSystem/AudioLoader.h"

class RIFFBinaryReader;

//class RIFFBinaryReader;
enum class LoadSize
{
	BytePerSec,	// 秒単位
	BytePerSam,	// サンプル単位
};

class WAVLoader final : public Engine::AudioSystem::AudioLoader
{
private:
	using base = Engine::AudioSystem::AudioLoader;
private:
	RIFFBinaryReader* m_reader;
	LoadSize m_loadSize;
	uint32_t m_startPosition;	// 読み込み開始位置
	uint32_t m_endPosition;		// 読み込み終了位置
	uint32_t m_dataStart;		// データ情報格納開始位置
	uint32_t m_dataSize;		// データサイズ

public:
	WAVLoader();

	virtual ~WAVLoader();

public:
	virtual std::shared_ptr<Engine::AudioSystem::AudioClip> Open(const std::string& filePath) override;

	uint32_t GetDataSize() const { return m_dataSize; }

	uint8_t* Load8(uint32_t loadSize);

	uint16_t* Load16(uint32_t loadSize);

	virtual void LoadBuffer(std::shared_ptr<Engine::AudioSystem::AudioBuffer> buffer, int32_t size = -1) override;

	void Reset();

};
