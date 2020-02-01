#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 塗りつぶし方法
		enum class FillType : uint8_t
		{
			WireFrame,	// ワイヤーフレーム
			Solid,		// 塗りつぶし
		};
	}
}