#pragma once

#ifdef __cplusplus
#include <DirectXMath.h>
#include <cstdint>
	using uint = uint32_t;
	using half = uint16_t;
	using float2 = DirectX::XMFLOAT4;
	using float3 = DirectX::XMFLOAT4;
	using float4 = DirectX::XMFLOAT4;
	using vector = float4;

	using float4x4 = DirectX::XMFLOAT4X4;
	using matrix = float4x4;

#endif
