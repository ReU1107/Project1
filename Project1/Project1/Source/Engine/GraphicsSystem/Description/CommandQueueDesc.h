#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class CommandQueuePriority : uint8_t;
		enum class CommandListType : uint8_t;

		struct CommandQueueDesc
		{
			CommandListType type;			// タイプ
			CommandQueuePriority priority;	// 優先度
		};
	}
}