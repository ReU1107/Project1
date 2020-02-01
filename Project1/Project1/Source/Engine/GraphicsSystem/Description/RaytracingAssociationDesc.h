#pragma once
#include <string>

/*
D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE

*/

namespace Engine
{

	namespace GraphicsSystem 
	{

		// シェーダーと他のサブリソースをバインド
		struct RaytracingAssociationDesc
		{
			const wchar_t** shaderNames;// バインドするシェーダー
			uint32_t shaderCount;		// バインドするシェーダー数
			uint32_t index;				// バインドするサブステートの格納先
			
		};
	}

}
