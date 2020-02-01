#pragma once
#include <string>

/*
D3D12_DXIL_LIBRARY
*/

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IShader;

		struct RaytracingShaderLibraryDesc
		{
			IShader* shader;				// シェーダーライブラリーオブジェクト
			const wchar_t** shaderNames;	// ライブラリー内のシェーダーのそれぞれの関数名
			uint32_t shaderCount;			// ↑のシェーダー数
		};

	}

}
