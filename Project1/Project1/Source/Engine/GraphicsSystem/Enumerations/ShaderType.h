#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderType : uint8_t
		{
			All,		// 全て		Raytracingはこれ
			Vertex,		// 頂点
			Hull,		// ハル
			Geometry,	// ジオメトリー
			Domain,		// ドメイン
			Pixel,		// ピクセル
		};
	}

}