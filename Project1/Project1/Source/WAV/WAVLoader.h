#pragma once
#include "../Engine/AudioSystem/AudioLoader.h"

class RIFFBinaryReader;

//class RIFFBinaryReader;
enum class LoadSize
{
	BytePerSec,	// �b�P��
	BytePerSam,	// �T���v���P��
};

class WAVLoader final : public Engine::AudioSystem::AudioLoader
{
private:
	using base = Engine::AudioSystem::AudioLoader;
private:
	RIFFBinaryReader* m_reader;
	LoadSize m_loadSize;
	uint32_t m_startPosition;	// �ǂݍ��݊J�n�ʒu
	uint32_t m_endPosition;		// �ǂݍ��ݏI���ʒu
	uint32_t m_dataStart;		// �f�[�^���i�[�J�n�ʒu
	uint32_t m_dataSize;		// �f�[�^�T�C�Y

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
