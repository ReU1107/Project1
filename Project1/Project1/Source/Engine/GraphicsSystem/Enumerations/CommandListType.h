#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class CommandListType : uint8_t
		{
			General,	// 全て積み込み可能
			Copy,		// コピーのみ
			Compute,	// コンピュート関連のみ
		};

	}
}