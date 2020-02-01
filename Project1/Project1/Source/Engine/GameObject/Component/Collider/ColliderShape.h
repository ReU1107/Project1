#pragma once
#include <cstdint>

namespace Engine
{

	/*
	コライダーの形状によって当たり判定のやり方が変わる
	*/

	// コライダーの形状
	enum class ColliderShape : uint8_t
	{
		Box,		// 箱
		Capsule,	// カプセル
		Sphere,		// 球
		Mesh,		// メッシュ
		Terrain		// 地形
	};

}