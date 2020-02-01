#pragma once
#include <cstdint>

namespace Engine
{

	// ライトのイベントタイミング
	enum class LightEvent
	{
		BeforeShadowMap,		// シャドウマップがレンダリングされる前
		AfterShadowMap,			// シャドウマップがレンダリングされた後
		BeforeScreenspaceMask,	// ディレクショナルライトのスクリーン空間のシャドウマスクが計算される前
		AfterScreenspaceMask,	// ディレクショナルライトスクリーン空間のシャドウマスクが計算された後
		BeforeShadowMapPass,	// シャドウマップパスがレンダリングされる前
		AfterShadowMapPass,		// シャドウマップパスがレンダリングされる後
	};
}