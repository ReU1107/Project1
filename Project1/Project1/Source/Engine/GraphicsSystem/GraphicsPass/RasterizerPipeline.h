#pragma once
#include <vector>
#include <array>
#include <cstdint>
#include "..//Description/BlendDesc.h"
#include "..//Description/InputLayoutDesc.h"
#include "..//Description/RasterizerDesc.h"
#include "..//Description/DepthStencilDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Shader;
		class Texture;
		class RootSignature;
		class IRasterizerPipeline;
		enum class ResourceFormat : uint8_t;
		enum class PrimitiveTopology : uint8_t;

		class RasterizerPipeline
		{
		private:
			using Textures = std::vector<Texture*>;

		private:
			IRasterizerPipeline* m_interface;		// インターフェイス
			Textures m_renderTargets;				// レンダーターゲット配列
			Shader* m_vertexShader;					// 頂点シェーダー
			Shader* m_pixelShader;					// ピクセルシェーダー
			Shader* m_domainShader;					// ドメインシェーダー
			Shader* m_hullShader;					// ハルシェーダー
			Shader* m_geometryShader;				// ジオメトリシェーダー
			RootSignature* m_rootSignature;			// ルートシグネチャ
			RasterizerDesc m_rasterizerState;		// ラスタライザーステート
			BlendDesc m_blendState;					// ブレンドステート
			InputLayoutDesc m_inputLayout;			// インプットレイアウト
			DepthStencilDesc m_depthStencilState;	// デプスステンシルステート
			uint32_t m_sampleCount;					// サンプルカウント
			uint32_t m_sampleQuality;				// サンプルクオリティ
			uint32_t m_renderTargetCount;			// レンダーターゲット数
			uint32_t m_nodeMask;					// ノードマスク
			uint32_t m_sampleMask;					// サンプルマスク
			PrimitiveTopology m_topology;			// 形状
			ResourceFormat m_renderTargetFormats[8];// レンダリングターゲットフォーマット
			ResourceFormat m_depthStencilFormat;	// デプスステンシルフォーマット
		public:
			// コンストラクタ
			RasterizerPipeline();
			// デストラクタ
			~RasterizerPipeline();
			// 頂点シェーダー設定
			void SetVertexShader(Shader* shader);
			// ピクセルシェーダー設定
			void SetPixelShader(Shader* shader);
			// ルートシグネチャ設定
			void SetRootSignature(RootSignature* rootSignature);
			// 入力レイアウト設定
			void SetInputLayout(const InputLayoutDesc& inputLayout);
			// ブレンドステート設定
			void SetBlendState(const BlendDesc& blendDesc);
			// ラスタライズステート設定
			void SetRasterizerState(const RasterizerDesc& rasterizerDesc);
			// デプスステンシルステート設定
			void SetDepthStencilState(const DepthStencilDesc& depthStencilDesc);
			// サンプルデスク設定
			void SetSampleDesc(uint32_t sampleCount = 1, uint32_t sampleQuality = 0);
			// レンダーターゲット数設定
			void SetRenderTargetCount(uint32_t renderTargetCount);
			// レンダーターゲットフォーマット設定
			void SetRenderTargetFormat(ResourceFormat format, int32_t index);
			// デプスステンシルフォーマット設定
			void SetDepthStencilFormat(ResourceFormat format);

			void Create();
			// インターフェイス取得
			IRasterizerPipeline* GetInterface() const;
			// ルートシグネチャ取得
			RootSignature* GetRootSignature() const;

			// 頂点シェーダー取得
			Shader* GetVertexShader() const;
			// ピクセルシェーダー取得
			Shader* GetPixelShader() const;

		};

	}
}