#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem 
	{
		// レイトレーシングサブステート
		enum class RaytracingPipelineParameterType : uint8_t
		{
			PipelineConfig,	// パイプラインコンフィグ
			ShaderConfig,	// シェーダーコンフィグ
			Association,	// アソシエーション
			ShaderLibrary,	// シェーダーライブラリー
			Signature,		// シグネチャ
			HitGroup,		// ヒットグループ
		};
	}
}