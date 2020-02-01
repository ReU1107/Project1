#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderResourceType : uint8_t
		{
			ConstantBuffer,		// 定数バッファ
			ShaderResource,		// シェーダーリソース
			ReadWriteResource,	// 読み書き可能リソース
			Sampler,			// サンプラー
		};

	}

}