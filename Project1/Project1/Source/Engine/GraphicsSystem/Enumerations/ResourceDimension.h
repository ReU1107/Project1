#pragma once
#include <cstdint>
namespace Engine
{
	namespace GraphicsSystem 
	{
		enum class ResourceDimension : uint8_t
		{
			Unknown,	// テクスチャタイプが初期化されていないか、不明です。
			None,		// テクスチャが指定されていません。
			Any,		// すべてのテクスチャタイプ。
			Tex1D,		// 1Dテクスチャ
			Tex2D,		// 2Dテクスチャ(Texture2D)。
			Tex3D,		// 3Dボリュームテクスチャ(Texture3D)。
			Cube,		// キューブマップ テクスチャ。
			Tex2DArray,	// 2D配列テクスチャ(Texture2DArray)。
			CubeArray,	// Cubemap array texture(CubemapArray).
		};
	}
}