#pragma once
#include <cstdint>

namespace Engine 
{
	
	enum class DepthTextureMode : uint8_t
	{
		None,			// 深度テクスチャを生成しない
		Depth,			// 深度値のみ生成
		DepthNormals,	// 深度,法線生成
		MotionVectors	// モーションベクター作成
	};

}