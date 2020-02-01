#pragma once
#include <cstdint>

namespace Engine
{

	// カメラのコマンドバッファ実行タイミング
	enum class CameraEvent
	{
		BeforeDepthTexture,			// カメラのデプステクスチャが生成される前
		AfterDepthTexture,			// カメラのデプステクスチャが生成された後
		BeforeDepthNormalsTexture,	// カメラのデプス + 法線テクスチャが生成される前
		AfterDepthNormalsTexture,	// カメラのデプス + 法線テクスチャが生成される前
		BeforeGBuffer,				// 遅延レンダリングでGBufferがレンダリングされる前
		AfterGBuffer,				// 遅延レンダリングでGBufferがレンダリングされた後
		BeforeLighting,				// 遅延レンダリングで Lighting Pass の前
		AfterLighting,				// 遅延レンダリングで Lighting Pass の後
		BeforeFinalPass,			// 遅延レンダリングで Final Geometry Pass の前
		AfterFinalPass,				// 遅延レンダリングで Final Geometry Pass の後
		BeforeForwardOpaque,		// 即時レンダリングでオペークオブジェクトの前
		AfterForwardOpaque,			// 即時レンダリングでオペークオブジェクトの後
		BeforeImageEffectsOpaque,	// オペークオブジェクトとトランスペアレントオブジェクト間で発生するイメージエフェクトの前
		AfterImageEffectsOpaque,	// オペークオブジェクトとトランスペアレントオブジェクト間で発生するイメージエフェクトの後
		BeforeSkybox,				// スカイボックスを描画する前
		AfterSkybox,				// スカイボックスを描画した後
		BeforeForwardAlpha,			// 即時レンダリングでトランスペアレントオブジェクトの前
		AfterForwardAlpha,			// 即時レンダリングでトランスペアレントオブジェクトの後
		BeforeImageEffects,			// イメージエフェクトの前
		AfterImageEffects,			// イメージエフェクトの後
		AfterEverything,			// カメラがすべてのレンダリングを行った後
		BeforeReflections,			// 遅延レンダリングで Reflections Pass の前
		AfterReflections,			// 遅延レンダリングで Reflections Pass の後
		BeforeHaloAndLensFlares,	// レンズフレアとブロッケン現象の前
		AfterHaloAndLensFlares,		// レンズフレアとブロッケン現象の後
	};
}