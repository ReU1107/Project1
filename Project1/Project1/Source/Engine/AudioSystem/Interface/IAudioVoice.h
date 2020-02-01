#pragma once
#include "IAudioComponent.h"
#include <functional>

/*
PCM(�p���X�����ϒ�)
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// �O���錾
		class IAudioBuffer;
		class IAudioSubMixer;
		class IAudioMixerGroup;

		struct AudioBufferDesc
		{
			void* data;						// �f�[�^
			uint32_t sampleCount;			// �T���v���J�E���g
			uint32_t startPosition;			// �J�n�ʒu
			uint32_t playLength;			// �Đ����钷��
			uint32_t loopStartPosition;		// ���[�v�J�n�ʒu
			uint32_t loopLength;			// ���[�v���钷��
			uint32_t loopCount;				// ���[�v��
		};

		// �����
		class __declspec(uuid("5CB8B981-A3A4-4E3F-B6CC-F5E5BAA8C325")) IAudioVoice : public IAudioComponent
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~IAudioVoice() {}

			// �Đ��J�n
			virtual void Start() = 0;
			// �Đ��ꎞ��~
			virtual void Pause() = 0;
			// �Đ����S��~
			virtual void Stop() = 0;

			// �{�����[���ݒ�
			virtual void SetVolume(float volume) = 0;

			// PCM�f�[�^����
			virtual void SubmitBuffer(const AudioBufferDesc& buffer) = 0;

			// �O���[�v�ݒ�
			virtual void SetGroups(IAudioSubMixer* groups[], uint32_t count) = 0;

			// �G�t�F�N�g�L����
			virtual void EnableEffect(int32_t index) = 0;
			// �G�t�F�N�g������
			virtual void DisableEffect(int32_t index) = 0;

			// �Đ����̃o�b�t�@���I�����ɌĂ΂��֐��ݒ�
			virtual void SetBufferEndFunction(const std::function<void()>& function) = 0;

		};

	}

}