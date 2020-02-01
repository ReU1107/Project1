#pragma once
#include <cstdint>

namespace Engine
{

	// 種類
	enum class LightType : uint8_t
	{
		Directional,	// 平行光源(指向性)
		Point,			// 点光源
		Spot,			// スポットライト
		Area			// エリア
	};
}