#pragma once
#include "../Interface/IAudioEffect.h"

// 前方宣言
struct IXAPO;

namespace Engine 
{

	namespace AudioSystem 
	{

		class DXA2AudioEffect final : public IAudioEffect
		{
		private:
			using base = IAudioEffect;
		private:
			IXAPO* m_nativeEffect;

		public:
			// コンストラクタ
			DXA2AudioEffect();
			// デストラクタ
			~DXA2AudioEffect();
		public:
			// 
			virtual void* GetNativeEffect() const override;

			virtual bool IsValid() const override { return true; }
		};

	}

}
