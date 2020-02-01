#pragma once
#include <cstdint>
#include "IUnknown.h"

/*
音情報を操作する
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// 前方宣言
		class IAudioEffect;

		class IAudioComponent //: public IUnknown
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioComponent() {}
			// 低レベルAPI生ポインタ取得
			virtual void* GetNativeVoice() const = 0;

			// エフェクト設定
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) = 0;

		};

	}

}