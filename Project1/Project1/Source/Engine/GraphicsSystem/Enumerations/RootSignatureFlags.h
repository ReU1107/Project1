#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class RootSignatureFlags : uint8_t
		{
			None = 0,								// なし
			AllowInputAssemblerInputLayout = 0x1,	// インプットアセンブラ,レイアウト指定可
			DenyVertexShaderRootAccess = 0x2,		// 頂点シェーダーでアクセスしない
			DenyHullShaderRootAccess = 0x4,			// ハルシェーダーでアクセスしない
			DenyDomaionShaderRootAccess = 0x8,		// ドメインシェーダーでアクセスしない
			DenyGeometryShaderRootAccess = 0x10,	// ジオメトリシェーダーでアクセスしない
			DenyPixelShaderRootAccess = 0x20,		// ピクセルシェーダーでアクセスしない
			AllowStreamOutput = 0x40,				// ストリームアウト先指定か
			LocalRootSignature = 0x80				// ローカルルートシグネチャとして使用
		};

	}

}