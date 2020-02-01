#pragma once

/*
オーディオエフェクトを拡張して
新しく作成する場合はこのクラスを継承してください
*/

namespace Engine 
{

	namespace AudioSystem 
	{

		class __declspec(uuid("F7972759-297C-44F5-8E54-4C5BED5A393B")) IAudioEffect
		{
		public:
			virtual ~IAudioEffect() {}

			// 低レベルAPI取得
			virtual void* GetNativeEffect() const = 0;
			
			// 有効か無効か
			virtual bool IsValid() const = 0;
			

		};

	}

}