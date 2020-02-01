#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class GraphicsCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using GraphicsCommandListPtr = std::shared_ptr<GraphicsCommandList>;
		public:
			// コンストラクタ
			GraphicsCommandList();
			// デストラクタ
			virtual ~GraphicsCommandList();

			static GraphicsCommandListPtr Create(const std::string& name);

		public:
			// レンダーターゲット内容クリア
			virtual void ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color = Color4::White) const override;

			// デプスステンシル内容クリア
			virtual void ClearDepthStencil(ResourceView* view, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const override;

			// 頂点バッファ配列設定
			virtual void SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start = 0) const override;

			// インデックスバッファ設定
			virtual void SetIndexBuffer(IndexBuffer* indexBuffer) const override;

			// プリミティブ設定
			virtual void SetTopology(PrimitiveTopology topology) const override;

			// ビューポート配列設定
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const override;

			// シザーレクト配列設定
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const override;

			// レンダーターゲット配列,デプスステンシル設定
			virtual void SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const override;

			// デスクリプターヒープ配列設定
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const override;

			// ラスタライザーパイプライン設定
			virtual void SetRasterizerPipeline(RasterizerPipeline* pipeline) const override;

			// 定数バッファ　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const override;

			// シェーダーリソース　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const override;

			// アンオーダードアクセス　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const override;

			// ルートシグネチャ設定　(グラフィックス)
			virtual void SetGraphicsRootSignature(RootSignature* rootSignature) const override;

			// デスクリプターテーブル設定 必要な情報が連続で作成されている必要あり(グラフィックス)
			virtual void SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const override;

			// リソースバリアー
			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const override;

			// 描画
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const override;

			// レイトレーシング実行
			virtual void DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const override;

			// レイトレーシングジオメトリ作成
			virtual void BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const override;

			// レイトレーシングシーン生成
			virtual void BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const override;

			// レイトレーシングパイプライン設定
			virtual void SetRaytracingPipeline(RaytracingPipeline* pipeline) const override;

			// コンピュートパイプライン設定
			virtual void SetComputePipeline(ComputePipeline* pipeline) const override;

			// 定数バッファ　ビューを介さず設定(コンピュート)
			virtual void SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const override;

			// シェーダーリソース　ビューを介さず設定(コンピュート)
			virtual void SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const override;

			// アンオーダードアクセス　ビューを介さず設定(コンピュート)
			virtual void SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const override;

			// ルートシグネチャ設定　(コンピュート)
			virtual void SetComputeRootSignature(RootSignature* rootSignature) const override;

			// デスクリプターテーブル設定 必要な情報が連続で作成されている必要あり(コンピュート)
			virtual void SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const override;
			virtual void SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const override;

			// コンピュートシェーダー実行
			virtual void DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const override;

			// 
			virtual void UnorderedAccessBarrier(Resource* resources[], uint32_t count) const override;

			virtual void UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const override;

			// リソースコピー
			virtual void CopyResource(Resource* source, Resource* destination) const override;


			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const override;

			virtual void CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset = 0, uint32_t dstOffset = 0) const;
			virtual void CopyBuffer(Buffer* buffer) const override;
		};

	}
}