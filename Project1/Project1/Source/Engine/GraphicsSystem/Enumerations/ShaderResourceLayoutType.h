#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{


		enum class ShaderResourceLayoutType : uint8_t
		{
			DescriptorTable,	// デスクリプターテーブル
			Constants,			// 定数
			Descriptor,			// 
		};

	}

}