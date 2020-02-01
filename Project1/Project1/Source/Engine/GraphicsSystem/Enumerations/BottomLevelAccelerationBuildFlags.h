#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem
	{

		enum class BottomLevelAccelerationBuildFlags : uint8_t
		{
			AllowCompaction = 0x01,	// 圧縮許可
			AllowUpdate = 0x02,		// 更新許可
			MinimizeMemory = 0x04,	// メモリ最小化
			PerformUpdate = 0x08,	// 更新実行
			PreferFastBuild = 0x10,	// 素早い構築
			PreferFastTrace = 0x20,	// 素早いトレース
		};
	}
}