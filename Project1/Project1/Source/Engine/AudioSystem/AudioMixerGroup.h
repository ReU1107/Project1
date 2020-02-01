#pragma once
#include <list>
#include "../Utility/AccessObject.h"
/*
複数のAudioClipに対して同じ
エフェクトを掛けたいなどしたいときに使用する
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// 前方宣言
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
			Clips m_clips;				// オーディオクリップ配列
			IAudioSubMixer* m_subMixer;	// ミキサー

		public:
			// コンストラクタ
			AudioMixerGroup(const std::string& name);
			// デストラクタ
			virtual ~AudioMixerGroup();

			static AudioMixerGroupPtr Create(const std::string& name);

		public:
			// オーディオクリップ追加
			void AddAudioClip(AudioClipPtr clip);

		};

	}
}