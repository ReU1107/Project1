#include "WAVLoader.h"
#include "RIFFBinaryReader.h"
#include "RIFFDataModel.h"
#include <fstream>
#include "../Engine/AudioSystem/Include.h"

using namespace Engine;
using namespace Engine::AudioSystem;

WAVLoader::WAVLoader()
	: m_reader(nullptr)
	, m_loadSize()
	, m_dataStart()
	, m_startPosition(0)
	, m_endPosition(0)
	, m_dataSize(0)
{
}

WAVLoader::~WAVLoader()
{
	delete m_reader;
}

std::shared_ptr<AudioClip> WAVLoader::Open(const std::string& filePath)
{

	m_reader = new RIFFBinaryReader(filePath);
	
	// ヘッダ情報読み込み
	RIFFHeader header(*m_reader);

	uint32_t currentPos = sizeof(header);

	std::shared_ptr<AudioClip> clip;
	uint32_t frequency = 0;
	uint32_t channelCount = 0;
	uint32_t bitDepth = 0;

	// データ格納先まで移動
	while (true) 
	{
		// サイズ以上を読み込もうとしたら終了
		if (currentPos > header.size) 
		{
			break;
		}

		RIFFChunk chunk(*m_reader);
		currentPos += sizeof(chunk);

		// フォーマットチャンク
		if (!strncmp(chunk.id, "fmt ", 4)) 
		{
			// フォーマットデータ読み込み
			WAVEFormat format(*m_reader);

			currentPos += sizeof(format);
			frequency = format.frequency;
			channelCount = format.channelCount;
			bitDepth = format.depth;

		}
		// データチャンクなら
		else if (!strncmp(chunk.id,"data",4))
		{
			m_dataSize = chunk.size;
			break;
		}
		else if (!strncmp(chunk.id, "LIST", 4))
		{
			WAVEList list(*m_reader);
		}
		else if (!strncmp(chunk.id, "ISFT", 4))
		{
			WAVEISFT isft(*m_reader);
		}
		else
		{
			currentPos += chunk.size;
		}
	}
	/*
	分割数を2の累乗にしないと再生できない
	たまに逆の場合もある
	*/
	// クリップを作成したら抜ける
	clip = AudioClip::Create(filePath, frequency, channelCount, bitDepth, m_dataSize, 1024);

	m_dataStart = currentPos;
	m_startPosition = currentPos;

	return clip;
}


uint8_t* WAVLoader::Load8(uint32_t loadSize)
{
	uint32_t m_startPos = 0;
	uint32_t m_currentPos = 0;
	uint32_t m_maxSize = 0;
	// 読み込み終了を超えそうならその差分だけ読み込む
	if (m_maxSize < m_currentPos + loadSize)
	{
		loadSize = m_maxSize - m_currentPos;

		// 読み込み開始位置に戻す
		m_currentPos = m_startPos;

		m_reader->Seek(SeekPosition::Begin, m_dataStart + m_startPos);
	}
	uint8_t* data = new uint8_t[loadSize];
	m_currentPos += m_reader->Read(data, loadSize);

	return data;
}

uint16_t* WAVLoader::Load16(uint32_t loadSize)
{
	uint32_t m_startPos = 0;
	uint32_t m_currentPos = 0;
	uint32_t m_maxSize = 0;
	// 読み込み終了を超えそうならその差分だけ読み込む
	if (m_maxSize < m_currentPos + loadSize)
	{

		loadSize = m_maxSize - m_currentPos;

		// 読み込み開始位置に戻す
		m_currentPos = m_startPos;

		m_reader->Seek(SeekPosition::Begin, m_dataStart + m_startPos);
	}
	uint16_t* data = new uint16_t[loadSize];
	m_reader->Read(data, loadSize);

	// 
	m_currentPos += loadSize;

	return data;
}

void WAVLoader::LoadBuffer(std::shared_ptr<AudioBuffer> buffer, int32_t loadSize)
{
	uint32_t size = 0;
	if (loadSize < 0)
	{
		size = m_dataSize;
	}
	else
	{
		size = loadSize;
	}

	// 読み込み終了を超えそうならその差分だけ読み込む
	if (size > m_dataSize)
	{
		size = m_dataSize - m_startPosition;
	}

	m_startPosition += m_reader->Read(buffer->GetData(), size);
}

void WAVLoader::Reset()
{
	m_reader->Seek(SeekPosition::Begin, m_dataStart);
}
