#pragma once
#include <cstdint>
#include "InputLayoutDesc.h"
#include "RasterizerDesc.h"
#include "BlendDesc.h"
#include "DepthStencilDesc.h"
#include "..//Enumerations/PrimitiveTopology.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRootSignature;
		class IShader;
		enum class ResourceFormat : uint8_t;

		struct RasterizerPipelineDesc
		{
			IRootSignature* rootSignature;			// ルートシグネチャ
			InputLayoutDesc inputLayout;			// インプットレイアウト
			RasterizerDesc rasterizerState;			// ラスタライザーステート
			BlendDesc blendState;					// ブレンドステート
			DepthStencilDesc depthStencil;			// デプスステンシルステート
			IShader* vertexShader;					// 頂点シェーダー
			IShader* domainShader;					// ドメインシェーダー
			IShader* hullShader;					// ハルシェーダー
			IShader* geometryShader;				// ジオメトリーシェーダー
			IShader* pixelShader;					// ピクセルシェーダー
			uint32_t renderTargetCount;				// レンダーターゲット数
			uint32_t sampleMask;					// サンプルマスク
			uint32_t nodeMask;						// ノードマスク
			uint32_t sampleCount;					// サンプルカウント
			uint32_t sampleQuality;					// サンプルクオリティ
			PrimitiveTopology topology;				// トッポロジー
			ResourceFormat renderTargetFormats[8];	// レンダーターゲットフォーマット配列
			ResourceFormat depthStencilFormat;		// デプスステンシルフォーマット
		};
		/*
		D3D12_STREAM_OUTPUT_DESC StreamOutput;
		D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;
		D3D12_CACHED_PIPELINE_STATE CachedPSO;
		 Flags;
		*/
		
	}

}