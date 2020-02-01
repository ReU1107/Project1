#pragma once
#include <cstdint>
namespace Engine 
{
	// シャドウキャスティング方法
	enum class ShadowCastingMode : uint8_t
	{
		Off,			// 影を落とさない
		On,				// 影を落とす
		TwoSided,		// ？
		ShadowsOnly,	// 影を落とすが存在しないものとして扱う(影は見えるが実体は見えない)
	};
}
