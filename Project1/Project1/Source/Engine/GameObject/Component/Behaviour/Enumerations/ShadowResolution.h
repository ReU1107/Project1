#pragma once
#include <cstdint>

namespace Engine
{

	// 解像度タイプ(指定するとデフォルトの解像度になる)
	enum class ShadowResolutionType : uint8_t
	{
		None,
		Low,				// 低解像度
		Medium,				// 中解像度
		QualitySettings,	// デフォルト設定
		High,				// 高解像度
		VeryHigh			// 非常に高い解像度
	};

	// シャドウマップの解像度(enum classが整数値しか設定できない為)
	struct ShadowResolution
	{
		static constexpr float Low = 0.5f;				// 低解像度
		static constexpr float Medium = 0.75f;			// 中解像度
		static constexpr float QualitySettings = 1.0f;	// デフォルト設定
		static constexpr float High = 2.0f;				// 高解像度
		static constexpr float VeryHigh = 4.0f;			// 非常に高い解像度
	};
}