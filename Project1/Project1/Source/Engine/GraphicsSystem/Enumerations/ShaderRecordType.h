#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class ShaderRecordType : uint8_t
		{
			RayGenerate,	// レイ生成
			HitGroup,		// ヒットグループ
			Miss,			// ミス
			Callable,		// 
		};

	}

}