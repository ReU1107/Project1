#pragma once
#include <cstdint>

namespace Engine 
{

	namespace AudioSystem
	{

		// 読み込み方法
		enum class AudioClipLoadType : uint8_t
		{
			DecompressOnLoad,	// 解凍状態で一括でメモリに格納
			CompressedInMemory,	// 圧縮状態
			Streaming,			// ストリーミング
		};

	}

}