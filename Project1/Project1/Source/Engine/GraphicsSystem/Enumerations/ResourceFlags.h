#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// リソースの使用許可申請みたいなもの
		enum class ResourceFlags : uint8_t
		{
			None = 0x0,						// なし
			AllowRenderTarget = 0x01,		// 描画先指定許可
			AllowDepthStencil = 0x02,		// 深度、ステンシル書き込み許可
			AllowUnorderedAccess = 0x04,	// コンピュートシェーダーのアクセス許可
			DenyShaderResource = 0x08,		// シェーダーリソース指定不許可
			AllowCrossAdapter = 0x10,		// 別々のアダプターでの使用許可
			AllowSimultaneousAccess = 0x20,	// 
			DecodeReferenceOnly = 0x40,		// 
		};

	}

}