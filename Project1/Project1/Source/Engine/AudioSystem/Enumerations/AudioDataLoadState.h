#pragma once
#include <cstdint>

namespace Engine
{

	namespace AudioSystem 
	{
	
		// 読み込み状況
		enum class AudioDataLoadState : uint8_t
		{
			Unloaded,	// 読み込まれたオーディオデータが無く、ローディングがまだ開始されていない AudioClip に関して AudioClip.loadState によって返される値です。
			Loading,	// 現在オーディオデータをローディング中の AudioClip に関して AudioClip.loadState が返す値です。
			Loaded,		// オーディオデータのローディングに成功した AudioClip に関して AudioClip.loadState が返す値です。
			Failed,		// オーディオデータのローディングに失敗した AudioClip に関して AudioClip.loadState が返す値です。
		};
	}
}