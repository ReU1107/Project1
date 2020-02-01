#pragma once
#include "../Interface/IAudioSubMixer.h"

struct IXAudio2SubmixVoice;

namespace Engine 
{

	namespace AudioSystem
	{

		class DXA2AudioSubMixer final : public IAudioSubMixer
		{
		private:
			using base = IAudioSubMixer;
			friend class DXA2Device;
		private:
			IXAudio2SubmixVoice* m_native;
		public:
			// �R���X�g���N�^
			DXA2AudioSubMixer();
			// �f�X�g���N�^
			virtual ~DXA2AudioSubMixer();

			// �჌�x��API���|�C���^�擾
			virtual void* GetNativeVoice() const override { return nullptr; }

			// �G�t�F�N�g�ݒ�
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) override{}

		};

	}

}