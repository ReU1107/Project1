#pragma once
#include <vector>
#include <array>
#include "../Utility/AccessObject.h"
#include "Enumerations/DigitalFormat.h"

/*
FMOD::Studio �� event�I�Ȉ���
*/

/*
unity �͔g�`�f�[�^�ǂݍ��݂�
���g�ŋL�q����K�v������
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
			AudioMixerGroups m_groups;			// �O���[�v�z��
			AudioBuffers m_buffers;				// �o�b�t�@�z��

			IAudioVoice* m_voice;				// �{�C�X

			uint32_t m_frequency;				// �T���v�����g��

			uint32_t m_divisionCount;			// �o�b�t�@������
			uint32_t m_currentIndex;			// ���ݏ������̃o�b�t�@�ԍ�
			uint32_t m_bufferSize;				// 

			AudioEffectLayout m_effectLayout;	// �G�t�F�N�g���C�A�E�g

			uint8_t m_channelCount;				// �`�����l����
			uint8_t m_bitDepth;					// �g�p�r�b�g��

			AudioClipLoadType m_loadType;		// �ǂݍ��ݕ��@
			AudioDataLoadState m_loadState;		// �ǂݍ��ݏ�
			State m_state;
		public:
			// �R���X�g���N�^
			AudioClip(const std::string& name);
			// �f�X�g���N�^
			virtual ~AudioClip();
		public:
			// �I�[�f�B�I�N���b�v�쐬
			static AudioClipPtr Create(const std::string& name, uint32_t frequency, uint32_t channelCount, uint32_t bitDepth, uint32_t bufferSize, uint32_t divisionCount = 1, DigitalFormat format = DigitalFormat::PCM);

		public:
			// �O���[�v�ɏ���
			void EntryToGroup(AudioMixerGroupPtr group);

			// �O���[�v���E��
			void ExitFromGroup(AudioMixerGroupPtr group);

			// �o�b�t�@��
			void BufferEnd();

			// �G�t�F�N�g
			void AddEffect(AudioEffectLayout layout);

			// �J�n
			void Start();

			// �ꎞ��~
			void Pause();

			// �ĊJ�n
			void Restart();

			// ���S��~
			void Stop();

		public:

			// ���g���擾
			uint32_t GetFrequency() const;
			// �`�����l�����擾
			uint8_t GetChannelCount() const;
			// �r�b�g�[�x�擾
			uint8_t GetBitDepth() const;

			// �o�b�t�@�p�ɓǂݍ��ރT�C�Y�擾
			uint32_t GetLoadSize() const;

			// �Đ����̃o�b�t�@�擾
			AudioBufferPtr GetCurrentBuffer() const;
			// ���ɍĐ�����o�b�t�@�擾
			AudioBufferPtr GetNextBuffer() const;

			std::function<void()> CallBack;
		};
	}
	
}

using AudioClipPtr = std::shared_ptr<Engine::AudioSystem::AudioClip>;