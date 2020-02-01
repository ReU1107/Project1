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
			PCMBitStream m_pcmBitStream;// �f�[�^�z��
			PCMBitCount m_pcmBitCount;	// 1�T���v��������̃r�b�g��
			uint32_t m_sampleCount;		// �T���v����
			uint32_t m_startPosition;	// �o�b�t�@���ł̊J�n�ʒu   
			uint32_t m_playLength;		// �o�b�t�@���ł̍Đ��͈�	
			uint32_t m_loopPosition;	// ���[�v�J�n�ʒu
			uint32_t m_loopCount;		// ���[�v��

		public:
			// �R���X�g���N�^
			AudioBuffer();
			// �f�X�g���N�^
			~AudioBuffer();
		public:
			// �o�b�t�@�쐬
			static AudioBufferPtr Create(PCMBitCount bitCount, uint32_t size);
			
		public:

			// �J�n�ʒu�ݒ�
			void SetStartPosition(uint32_t startPosition = 0);
			// �Đ����ݒ�
			void SetPlayLength(uint32_t playLength);
			// ���[�v�J�n�ʒu�ݒ�
			void SetLoopPosition(uint32_t loopPosition = 0);
			// ���[�v���ݒ�
			void SetLoopCount(uint32_t loopCount = 255);

			// �f�[�^�T�C�Y�擾
			uint32_t GetSampleCount() const;

			// �f�[�^�擾
			void* GetData() const;

			// �Đ��J�n�ʒu�擾
			uint32_t GetStartPosition() const ;

			// �Đ����钷���擾
			uint32_t GetPlayLength() const;

			// ���[�v�J�n�ʒu�擾
			uint32_t GetLoopPosition() const;

			// ���[�v���擾
			uint32_t GetLoopCount() const;

		};
	}
}

using AudioBufferPtr = std::shared_ptr<Engine::AudioSystem::AudioBuffer>;