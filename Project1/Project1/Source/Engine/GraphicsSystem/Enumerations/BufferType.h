#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class BufferType : uint8_t
		{
			Vertex,		// 頂点
			Index,		// インデックス
			Constant,	// 定数
			Structure,	// 構造体
		};
	}
}