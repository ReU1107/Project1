#pragma once
#include "Behaviour.h"

namespace Engine
{
	namespace AudioSystem
	{
		class AudioClip;
	}
	// 音鳴らす
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
		bool m_is3D;			// 3Dの計算に入れるか

	public:
		AudioSource() noexcept;

		virtual ~AudioSource() noexcept;

		// インスタンスID
		static const InstanceID ID() { return InstanceID::AudioSource; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::AudioSource; }

	public:
		// クリップ設定
		void SetClip(AudioClipPtr clip);

		// クリップ取得
		AudioClipPtr GetClip() const;

		// 再生開始
		void Start();

		// 一時停止
		void Pause();

		// 再開
		void Restart();

		// 停止
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