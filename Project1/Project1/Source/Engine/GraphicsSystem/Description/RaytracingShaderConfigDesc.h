#pragma once
#include <cstdint>

/*
D3D12_RAYTRACING_SHADER_CONFIG
*/

/*
payload		レイトレースが終了した際に返される情報
float3 color等
attribute	衝突判定が起こった際に返される情報
float2 xy;	当たった三角形のそれぞれの割合値等
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{
		// レイトレーシングシェーダー情報
		struct RaytracingShaderConfigDesc
		{
			uint32_t attributeSize;		// 属性情報格納サイズ
			uint32_t payloadSize;		// 
		};
	}
}

