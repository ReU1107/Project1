#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// テクスチャの使用法
		enum class TextureUsage : uint8_t
		{
			ShaderResource,	// シェーダーリソース
			RenderTarget,	// レンダーターゲット
			DepthStencil,	// デプスステンシル
		};

	}

}