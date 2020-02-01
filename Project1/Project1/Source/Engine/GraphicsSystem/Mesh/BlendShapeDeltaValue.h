#pragma once
#include <cstdint>
#include "../../Math/Include.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		// ブレンドする形状の差分値
		struct BlendShapeDeltaPosition
		{
			uint32_t index;	// 変更する頂点番号
			Vector3 value;	// 差分位置
		};

		// ブレンドする形状の差分値
		struct BlendShapeDeltaNormal
		{
			uint32_t index;	// 変更する頂点番号
			Vector3 value;	// 差分法線
		};

		// ブレンドする形状の差分値
		struct BlendShapeDeltaTangent
		{
			uint32_t index;	// 変更する頂点番号
			Vector4 value;	// 差分接線
		};

	}
}