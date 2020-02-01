#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		struct InputElementDesc;

		struct InputLayoutDesc
		{
			InputElementDesc* elements;	// エレメント配列
			uint32_t elementCount;	// エレメント数
		};
	}
}