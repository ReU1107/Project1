#pragma once
#include "../Interface/IAudioDevice.h"

// �O���錾
struct IXAudio2;
struct IXAudio2MasteringVoice;

namespace Engine
{

	namespace AudioSystem
	{

		/*
		DirectX Audio2
		XAudio2
		*/

		class DXA2Device final : public IAudioDevice
		{
		private:
			using base = IAudioDevice;
		private:
			IXAudio2* m_device;							// �f�o�C�X
			IXAudio2MasteringVoice* m_masteringVoice;	// 
		public:
			// �R���X�g���N�^
			DXA2Device();
			// �f�X�g���N�^
			~DXA2Device();

			// 
			virtual void Start() override;

			// 
			virtual void Stop() override;

			// �}�X�^�[�쐬
			virtual IAudioMaster* CreateMaster(const AudioMasterData& data) override;
			// �{�C�X�쐬
			virtual IAudioVoice* CreateVoice(const AudioVoiceData& data) override;
			// �T�u�~�L�T�[�쐬
			virtual IAudioSubMixer* CreateSubMixer(const AudioSubMixerData& data) override;

			// �G�t�F�N�g�쐬
			virtual IAudioEffect* CreateEffect(const AudioEffectData& data) override;

		};

	}

}