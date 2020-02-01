#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem
	{

		enum class DescriptorHeapType : uint8_t
		{
			Constant,			// 定数
			RenderTarget,		// レンダーターゲット
			DepthStencil,		// デプスステンシル
			ShaderResource,		// シェーダーリソース(定数と同じ)
			UnorderedAccess,	// アンオーダードアクセス(定数と同じ)
			Sampler,			// サンプラー
		};
	}
}