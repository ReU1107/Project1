#pragma once
#include <cstdint>

/*
DirectXの内部で
どのバージョンを使用するか決定する
現在11,12のみ

*/

namespace Engine
{

	namespace GraphicsSystem 
	{
	
		// 描画
		enum class API : uint8_t
		{
			DirectX,
			OpenGL
		};
	}
}