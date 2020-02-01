#pragma once
#include <string>
#include <cstdint>

/*
オープン関数は一度だけ読み込みを行う
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		class AudioClip;
		class AudioBuffer;
		/*
		オーディオデータ(PCMバッファ)読み込みクラス
		*/
		class AudioLoader
		{

		public:

			virtual std::shared_ptr<AudioClip> Open(const std::string& filePath) = 0;

			virtual void LoadBuffer(std::shared_ptr<AudioBuffer> buffer, int32_t size = -1) = 0;

		};

	}

}