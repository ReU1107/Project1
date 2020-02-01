#pragma once
#include "../Interface/IAudioVoice.h"
#include <xaudio2.h>

struct IXAudio2SourceVoice;

/*
�R�[���o�b�N�����𕪂���\��
*/

namespace Engine 
{

	namespace AudioSystem 
	{

		class IAudioListener;
		enum class AudioEffectLayout : uint16_t;

		class DXA2AudioVoice final : public IAudioVoice, public IXAudio2VoiceCallback
		{
		private:
			using base = IAudioVoice;
			friend class DXA2Device;
		private:
			IXAudio2SourceVoice* m_nativeVoice;			// �{�C�X
			std::function<void()> m_bufferEndFunc;
		private:
			// IXAudio2VoiceCallback�C���^�[�t�F�[�X�̃C�x���g�n���h��
			void __stdcall OnBufferStart(void* pBufferContext) override;
			void __stdcall OnBufferEnd(void* pBufferContext) override;
			void __stdcall OnLoopEnd(void* pBufferContext) override;
			void __stdcall OnStreamEnd() override;
			void __stdcall OnVoiceProcessingPassStart(UINT32 BytesRequired) override;
			void __stdcall OnVoiceProcessingPassEnd() override;
			void __stdcall OnVoiceError(void* pBufferContext, HRESULT Error) override;
		public:
			// �R���X�g���N�^
			DXA2AudioVoice();
			// �f�X�g���N�^
			~DXA2AudioVoice();

			// �჌�x��API���|�C���^�擾
			virtual void* GetNativeVoice() const override;
			// �Đ��J�n
			virtual void Start() override;
			// �Đ��ꎞ��~
			virtual void Pause() override;
			// �Đ����S��~
			virtual void Stop() override;

			virtual void SetVolume(float volume) override;

			// PCM����
			virtual void SubmitBuffer(const AudioBufferDesc& buffer) override;

			// �O���[�v�ݒ�
			virtual void SetGroups(IAudioSubMixer* groups[], uint32_t count) override;

			// �G�t�F�N�g�ݒ�
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) override;

			void SetEffects(AudioEffectLayout layout);

			// �G�t�F�N�g�L����
			virtual void EnableEffect(int32_t index) override;

			// �G�t�F�N�g������
			virtual void DisableEffect(int32_t index) override;


			virtual void SetBufferEndFunction(const std::function<void()>& function) override;

			// 
			//DeclareIUnknownInterfaces();

		};

	}

}


/*		virtual uint32_t AddRef() override;

		virtual uint32_t Release() override;

		virtual bool QueryInterface(const _GUID& guid, void** object) override;
*/