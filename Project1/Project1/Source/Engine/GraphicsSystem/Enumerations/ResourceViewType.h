#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		// リソースビューの種類
		enum class ResourceViewType : uint8_t
		{
			ShaderResource,		// シェーダーリソースビュー
			RenderTarget,		// レンダーターゲットビュー
			DepthStencil,		// デプスステンシルビュー
			UnorderedAccess,	// アンオーダードアクセスビュー
			ConstantBuffer,		// コンスタントバッファービュー
			Raytracing,			// レイトレーシング用(SRVと同じ)
		};

	}

}