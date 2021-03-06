#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem
	{
		// 頂点属性
		enum class VertexFormat : uint8_t
		{
			Float16,	// 16bit
			Float32,	// 32bit	基本的にこっち
		};

	}

}