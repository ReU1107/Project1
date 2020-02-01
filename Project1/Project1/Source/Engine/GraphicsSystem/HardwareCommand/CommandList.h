#pragma once
#include "..//..//Math/Color4.h"
#include <cstdint>
#include "../../Utility/AccessObject.h"
#include <iostream>

/*
派生先のクラスで関数を制限する
*/

namespace Engine
{
	struct Rect;
	struct Viewport;

	namespace GraphicsSystem
	{
		class ICommandList;
		class ResourceView;
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class Texture;
		class RenderTexture;
		class DepthTexture;
		class Resource;
		class ResourceDescriptor;
		class RasterizerPipeline;
		class RaytracingPipeline;
		class ComputePipeline;
		class RootSignature;
		class ShaderTable;
		class BottomLevelAccelerationStructure;
		class TopLevelAccelerationStructure;
		class Buffer;

		enum class PrimitiveTopology : uint8_t;
		enum class ResourceStates : uint16_t;

		// ハードウェアで行う処理をためるリスト
		class CommandList : public AccessObject<CommandList>
		{
		private:
			using base = AccessObject<CommandList>;
		protected:
			using RenderTexturePtr = std::shared_ptr<RenderTexture>;
			using DepthTexturePtr = std::shared_ptr<DepthTexture>;
			using BottomLevelAccelerationStructurePtr = std::shared_ptr<BottomLevelAccelerationStructure>;
			using TopLevelAccelerationStructurePtr = std::shared_ptr<TopLevelAccelerationStructure>;
		protected:
			ICommandList* m_interface;
		public:
			// コンストラクタ
			CommandList();
			// デストラクタ
			virtual ~CommandList();

			ICommandList* GetInterface() const;
		protected:
			// この範囲はグラフィクスコマンドリスト以外はアクセスできないようにします

			// レンダーターゲット内容クリア
			virtual void ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color = Color4::White) const;
			
			// デプスステンシル内容クリア
			virtual void ClearDepthStencil(ResourceView* view, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const;
			
			// 頂点バッファ配列設定
			virtual void SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start = 0) const;
			
			// インデックスバッファ設定
			virtual void SetIndexBuffer(IndexBuffer* indexBuffer) const;
			
			// プリミティブ設定
			virtual void SetTopology(PrimitiveTopology topology) const;
			
			// ビューポート配列設定
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const;
			
			// シザーレクト配列設定
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const;
			
			// レンダーターゲット配列,デプスステンシル設定
			virtual void SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const;
			
			// デスクリプターヒープ配列設定
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const;
			
			// ラスタライザーパイプライン設定
			virtual void SetRasterizerPipeline(RasterizerPipeline* pipeline) const;
			
			// 定数バッファ　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const;
			
			// シェーダーリソース　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const;
			
			// アンオーダードアクセス　ビューを介さず設定(グラフィックス)
			virtual void SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const;
			
			// ルートシグネチャ設定　(グラフィックス)
			virtual void SetGraphicsRootSignature(RootSignature* rootSignature) const;
			
			// デスクリプターテーブル設定 必要な情報が連続で作成されている必要あり(グラフィックス)
			virtual void SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const;
			
			// リソースバリアー
			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const;
			
			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const;

			// 描画
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount, uint32_t startIndex, uint32_t startVertex, uint32_t startInstance) const;
		protected:
			// レイトレーシング実行
			virtual void DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const;

			// レイトレーシングジオメトリ作成
			virtual void BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const;

			// レイトレーシングシーン生成
			virtual void BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const;

			// コンピュートパイプライン設定
			virtual void SetComputePipeline(ComputePipeline* pipeline) const;

			// レイトレーシングパイプライン設定
			virtual void SetRaytracingPipeline(RaytracingPipeline* pipeline) const;
			
			// 定数バッファ　ビューを介さず設定(コンピュート)
			virtual void SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const;
			
			// シェーダーリソース　ビューを介さず設定(コンピュート)
			virtual void SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const;
			
			// アンオーダードアクセス　ビューを介さず設定(コンピュート)
			virtual void SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const;
			
			// ルートシグネチャ設定　(コンピュート)
			virtual void SetComputeRootSignature(RootSignature* rootSignature) const;
			
			// デスクリプターテーブル設定 必要な情報が連続で作成されている必要あり(コンピュート)
			virtual void SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const;

			// デスクリプターテーブル設定
			virtual void SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const;

			// コンピュートシェーダー実行
			virtual void DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const;

			// アンオーダードアクセス
			virtual void UnorderedAccessBarrier(Resource* resources[], uint32_t count) const;
			virtual void UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const;

		protected:
			
			// リソースコピー
			virtual void CopyResource(Resource* source, Resource* destination) const;

			virtual void CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset = 0, uint32_t dstOffset = 0) const;
			virtual void CopyBuffer(Buffer* buffer) const;

		public:
			// コマンド発行終了
			void Close() const;
			// リストリセット
			void Reset() const;
		};

	}
}