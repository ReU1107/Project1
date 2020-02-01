#include "AudioBuffer.h"

namespace Engine
{
	
	namespace AudioSystem 
	{

		AudioBuffer::AudioBuffer()
			: m_pcmBitStream()
			, m_pcmBitCount()
			, m_sampleCount(0)
			, m_startPosition(0)
			, m_playLength(0)
			, m_loopPosition(0)
			, m_loopCount(0)
		{
		}

		AudioBuffer::~AudioBuffer()
		{
			delete[] m_pcmBitStream.bit8;
			m_pcmBitStream.bit8 = nullptr;
		}

		AudioBuffer::AudioBufferPtr AudioBuffer::Create(PCMBitCount bitCount, uint32_t sampleCount)
		{
			auto buffer = std::make_shared<AudioBuffer>();
			buffer->m_pcmBitCount = bitCount;
			buffer->m_sampleCount = sampleCount;
			switch (bitCount)
			{
			case PCMBitCount::Bit8:
				buffer->m_pcmBitStream.bit8 = new uint8_t[sampleCount];
				break;
			case PCMBitCount::Bit16:
				buffer->m_pcmBitStream.bit16 = new uint16_t[sampleCount];
				break;
			default:
				break;
			}

			return buffer;
		}

		void AudioBuffer::SetStartPosition(uint32_t startPosition)
		{
			m_startPosition = startPosition;
		}

		void AudioBuffer::SetPlayLength(uint32_t playLength)
		{
			m_playLength = playLength;
		}

		void AudioBuffer::SetLoopPosition(uint32_t loopPosition)
		{
			m_loopPosition = loopPosition;
		}

		void AudioBuffer::SetLoopCount(uint32_t loopCount)
		{
			m_loopCount = loopCount;
		}

		uint32_t AudioBuffer::GetSampleCount() const
		{
			return m_sampleCount;
		}

		void* AudioBuffer::GetData() const
		{
			return m_pcmBitStream.general;
		}

		uint32_t AudioBuffer::GetStartPosition() const
		{
			return m_startPosition;
		}

		uint32_t AudioBuffer::GetPlayLength() const
		{
			return m_playLength;
		}

		uint32_t AudioBuffer::GetLoopPosition() const
		{
			return m_loopPosition;
		}

		uint32_t AudioBuffer::GetLoopCount() const
		{
			return m_loopCount;
		}
	}
}