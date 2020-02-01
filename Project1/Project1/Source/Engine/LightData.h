#pragma once

#include "Utility/ShaderCommonData.h"
#include "Math/Color3.h"

struct LightData
{
	Engine::Color3 color;		// 色
	float3 position;	// 位置
	float3 direction;	// 向き
	float range;		// 範囲
	float angle;		// アングル

	uint type;			// 種類
};