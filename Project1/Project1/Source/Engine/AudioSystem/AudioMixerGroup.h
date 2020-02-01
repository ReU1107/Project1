#pragma once
#include <list>
#include "../Utility/AccessObject.h"
/*
������AudioClip�ɑ΂��ē���
�G�t�F�N�g���|�������Ȃǂ������Ƃ��Ɏg�p����
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// �O���錾
		class IAudioSubMixer;
		class AudioClip;

		class AudioMixerGroup final : public AccessObject<AudioMixerGroup>
		{
		private:
			using base = AccessObject<AudioMixerGroup>;
			using AudioClipPtr = std::shared_ptr<AudioClip>;
			using Clips = std::list<AudioClipPtr>;
			using AudioMixerGroupPtr = std::shared_ptr<AudioMixerGroup>;
		private:
			Clips m_clips;				// �I�[�f�B�I�N���b�v�z��
			IAudioSubMixer* m_subMixer;	// �~�L�T�[

		public:
			// �R���X�g���N�^
			AudioMixerGroup(const std::string& name);
			// �f�X�g���N�^
			virtual ~AudioMixerGroup();

			static AudioMixerGroupPtr Create(const std::string& name);

		public:
			// �I�[�f�B�I�N���b�v�ǉ�
			void AddAudioClip(AudioClipPtr clip);

		};

	}
}