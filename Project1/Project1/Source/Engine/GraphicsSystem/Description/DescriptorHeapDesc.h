#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class DescriptorHeapType : uint8_t;

		struct DescriptorHeapDesc
		{
			uint32_t count;				// 作成予定の数
			uint32_t nodeMask;			// 
			DescriptorHeapType type;	// 
			bool shaderAccess;			// シェーダーからアクセスするか
		};
	}
}