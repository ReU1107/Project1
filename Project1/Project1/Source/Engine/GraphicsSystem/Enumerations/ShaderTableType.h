#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		// シェーダーテーブル種類
		enum class ShaderTableType : uint8_t
		{
			Miss,			// 何も当たらなかった時呼ばれるシェーダー
			Hit,			// 何かに当たった時呼ばれるシェーダー
			Callable,		// 
		};

	}

}
