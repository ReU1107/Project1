#pragma once
#include <cstdint>

/*
D3D12_ROOT_SIGNATURE_DESC

*/

namespace Engine 
{

	namespace GraphicsSystem 
	{
		class IShader;
		enum class RootSignatureFlags : uint8_t;
		struct ShaderResourceLayoutDesc;

		struct RootSignatureDesc
		{
			ShaderResourceLayoutDesc* layouts;	// レイアウト配列
			IShader* shader;					// シェーダー
			uint32_t layoutCount;				// レイアウトの数
			RootSignatureFlags flags;			// フラグ
			bool staticSampler;					// サンプラーを使用するか
			bool isShader;						
		};
	}

}