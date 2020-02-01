#pragma once

namespace Engine 
{

	namespace AudioSystem 
	{
		// 前方宣言
		class IAudioEvent;

		class IAudioCallback
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioCallback(){}
			// イベント処理
			virtual void ReceiveEvent(IAudioEvent* audioEvent) = 0;

		};

	}

}