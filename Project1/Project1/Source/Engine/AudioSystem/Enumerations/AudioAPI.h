#pragma once
#include <cstdint>

namespace Engine 
{

	namespace AudioSystem
	{
		/*
		オーディオシステムに使用する
		低レベルAPI
		*/
		enum class AudioAPI : uint8_t
		{
			XAudio2,	// 
			OpenAL		// 
		};

	}

}