#pragma once
#include <cstdint>

/*
�I�[�f�B�I�̍Đ��@�\��������
�჌�x��API,SDK�ɃA�N�Z�X���邽�߂�
�f�o�C�X
���̃N���X���p�����č���Ă�������
���XAudio2�̃f�o�C�X�쐬�ς�
���O��DirectX Audio2��� DXA2Device
*/

namespace Engine
{

	namespace AudioSystem 
	{

		// �O���錾
		class IAudioMaster;
		class IAudioVoice;
		class IAudioSubMixer;
		class IAudioEffect;

		struct AudioMasterData;
		struct AudioVoiceData;
		struct AudioSubMixerData;
		struct AudioEffectData;

		/*
		�I�[�f�B�I�Đ�
		�჌�x��API�A�N�Z�X�f�o�C�X
		*/
		class __declspec(uuid("71314576-7723-4EB9-8980-4393A5D8E94F")) IAudioDevice
		{
		public:
			virtual ~IAudioDevice() {}
			
			// 
			virtual void Start() = 0;

			// 
			virtual void Stop() = 0;

			// �}�X�^�[�쐬
			virtual IAudioMaster* CreateMaster(const AudioMasterData& data) = 0;

			// �{�C�X�쐬
			virtual IAudioVoice* CreateVoice(const AudioVoiceData& data) = 0;
			// �T�u�~�L�T�[�쐬
			virtual IAudioSubMixer* CreateSubMixer(const AudioSubMixerData& data) = 0;

			// �G�t�F�N�g�쐬
			virtual IAudioEffect* CreateEffect(const AudioEffectData& data) = 0;

		};

	}
}