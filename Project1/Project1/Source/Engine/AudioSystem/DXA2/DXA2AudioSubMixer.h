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
			// コンストラクタ
			DXA2AudioSubMixer();
			// デストラクタ
			virtual ~DXA2AudioSubMixer();

			// 低レベルAPI生ポインタ取得
			virtual void* GetNativeVoice() const override { return nullptr; }

			// エフェクト設定
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) override{}

		};

	}

}