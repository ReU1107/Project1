#pragma once

/*
低レベルAudioVoiceと
AudioClipの値渡し的なクラス
*/

namespace Engine
{

	namespace AudioSystem 
	{

		class IAudioListener
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioListener() {}

			// バッファが無くなった
			virtual void OnBufferEnd() = 0;


		};

	}

}