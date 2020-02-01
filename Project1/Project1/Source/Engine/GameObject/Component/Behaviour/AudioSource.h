#pragma once
#include "Behaviour.h"

namespace Engine
{
	namespace AudioSystem
	{
		class AudioClip;
	}
	// ���炷
	class AudioSource final : public Behaviour
	{
	private:
		using base = Behaviour;
		using AudioSourcePtr = std::shared_ptr<AudioSource>;
		using AudioClipPtr = std::shared_ptr<AudioSystem::AudioClip>;
	public:
		static std::vector<AudioSourcePtr> allAudioSource;
	private:
		AudioClipPtr m_clip;	// 
		bool m_is3D;			// 3D�̌v�Z�ɓ���邩

	public:
		AudioSource() noexcept;

		virtual ~AudioSource() noexcept;

		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::AudioSource; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::AudioSource; }

	public:
		// �N���b�v�ݒ�
		void SetClip(AudioClipPtr clip);

		// �N���b�v�擾
		AudioClipPtr GetClip() const;

		// �Đ��J�n
		void Start();

		// �ꎞ��~
		void Pause();

		// �ĊJ
		void Restart();

		// ��~
		void Stop();

	};

	template<>
	inline std::shared_ptr<AudioSource> Component::Create()
	{
		auto audioSource = std::make_shared<AudioSource>();
		AudioSource::allAudioSource.push_back(audioSource);

		return audioSource;
	}

}