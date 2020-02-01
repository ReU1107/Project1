#pragma once
#include <cstdint>

/*
ShaderResouceの定数バッファ一つ分
*/
/*
D3D12_ROOT_CONSTANTS
*/

namespace Engine
{

	namespace GraphicsSystem
	{
		// sizeを指定した定数を配置する
		struct ShaderResourceConstantsDesc
		{
			uint32_t size;			// 大きさ
			uint32_t index;			// 場所
			uint32_t space;			// 空間
		};
	}

}