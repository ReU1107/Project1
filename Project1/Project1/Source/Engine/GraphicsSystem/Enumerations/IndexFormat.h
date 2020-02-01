#pragma once
#include <cstdint>
#include <dxgiformat.h>
namespace Engine 
{

	namespace GraphicsSystem 
	{
		// 頂点インデックスフォーマット
		enum class IndexFormat : uint8_t
		{
			UInt16,		// 16bit 2byte
			UInt32,		// 32bit 4byte
		};

	}
}