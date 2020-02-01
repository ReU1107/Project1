#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class PrimitiveTopology : uint8_t
		{
			PointList,		// 点
			LineList,		// 線
			LineStrip,		// 線
			TriangleList,	// 三角形
			TriangleStrip,	// 三角形
			Patch,			// パッチ(ジオメトリシェーダー参照)
		};

	}
}