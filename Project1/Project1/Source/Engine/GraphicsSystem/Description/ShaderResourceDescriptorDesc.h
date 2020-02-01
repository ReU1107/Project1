#pragma once
#include <cstdint>

/*
D3D12_ROOT_DESCRIPTOR
*/
namespace Engine 
{

	namespace GraphicsSystem
	{
		enum class ShaderResourceType : uint8_t;
		/*
		typeにsamplerを指定しないでください
		*/
		// 位置、空間にタイプのリソースを一つだけ配置する
		struct ShaderResourceDescriptorDesc
		{
			uint32_t index;			// 配置する位置
			uint32_t space;			// 配置する空間
			ShaderResourceType type;	// タイプ
		};
	}

}