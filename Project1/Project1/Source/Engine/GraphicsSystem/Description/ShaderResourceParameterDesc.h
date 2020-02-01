#pragma once
#include <cstdint>

/*
D3D12_DESCRIPTOR_RANGE
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderResourceType : uint8_t;

		struct ShaderResourceParameterDesc
		{
			uint32_t index;				// 配置する場所
			uint32_t count;				// 配置する数
			uint32_t space;				// 配置する空間
			ShaderResourceType type;	// 配置するリソースの種類
		};
	}

}