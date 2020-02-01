#pragma once
#include "..//Interface/ICommandList.h"
struct ID3D12GraphicsCommandList5;
struct ID3D12CommandAllocator;

namespace Engine
{
	namespace GraphicsSystem 
	{
		class D3D12CommandList final : public ICommandList
		{
		public:
			ID3D12GraphicsCommandList5* m_nativeList;
			ID3D12CommandAllocator* m_nativeAllocator;

		public:
			// コンストラクタ
			D3D12CommandList();
			// デストラクタ
			virtual ~D3D12CommandList();
			// 
			virtual void* GetNativeCommandList() const override;

			virtual void ClearRenderTarget(IResourceView* renderTargetView, const Rect& rect, float color[4]) const override;

			virtual void ClearDepthStencil(IResourceView* depthStencilView, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const override;

			virtual void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) const override;

			virtual void BuildBottomLevelAccelerationStructure(IAccelerationStructure* as) const override;

			// シーン作成コマンド発行
			virtual void BuildTopLevelAccelerationStructure(IAccelerationStructure* as) const override;

			// レイトレーシング実行コマンド発行
			virtual void DispatchRaytracing(const RaytracingDispatchDesc& desc) const override;
			// リソースの仕様方法を変更し意図しないアクセスを防ぎます
			virtual void ResourceBarrierTransition(IResource* resources[], uint32_t resourceCount, ResourceStates before, ResourceStates after, uint32_t subResourceCount = -1) const override;

			// ここで使用する全てのリソースが入っているデータ設定
			virtual void SetDescriptorHeaps(IDescriptorHeap* descriptorHeaps[], uint32_t heapCount = 1) const override;
			// デスクリプターテーブル設定(コンピュートシェーダー)
			virtual void SetComputeDescriptorTable(IResourceView* view, uint32_t parameterIndex) const override;
			virtual void SetComputeDescriptorTable(IDescriptorHeap* heap, uint32_t parameterIndex) const override;

			// シェーダーリソースビュー設定(コンピュートシェーダー)
			virtual void SetComputeShaderResource(IResource* resource, uint32_t parameterIndex) const override;
			// 定数バッファビュー設定(コンピュートシェーダー)
			virtual void SetComputeConstantBuffer(IResource* resource, uint32_t parameterIndex) const override;
			// アンオーダードアクセスビュー設定(コンピュートシェーダー)
			virtual void SetComputeUnorderedAccess(IResource* resource, uint32_t parameterIndex) const override;

			// 
			virtual void UnorderedAccessBarrier(IResource* resources[], uint32_t resourceCount) const override;
			// ルートシグネチャ設定(コンピュート)
			virtual void SetComputeRootSignature(IRootSignature* rootSignature) const override;
			// ルートシグネチャ設定(グラフィック)
			virtual void SetGraphicsRootSignature(IRootSignature* rootSignature) const override;
			// デスクリプターテーブル設定(グラフィック)
			virtual void SetGraphicsRootDescriptorTable(IResourceView* view, uint32_t index) const override;
			// シェーダーリソースビュー設定(グラフィック)
			virtual void SetGraphicsShaderResource(IResource* resource, uint32_t index) const override;
			// 定数ビュー設定(グラフィック)
			virtual void SetGraphicsConstantBuffer(IResource* resource, uint32_t index) const override;
			// アンオーダードアクセスビュー設定(グラフィック)
			virtual void SetGraphicsUnorderedAccess(IResource* resource, uint32_t index) const override;
			// レイトレーシングパイプライン設定
			virtual void SetRaytracingPipeline(IRaytracingPipeline* pipeline) const override;
			// ラスタライザーパイプライン設定
			virtual void SetRasterizerPipeline(IRasterizerPipeline* pipeline) const override;

			// コンピュートパイプライン設定
			virtual void SetComputePipeline(IComputePipeline* pipeline) const override;

			// プリミティブ設定
			virtual void SetPrimitiveTopology(PrimitiveTopology topology) const override;
			// 頂点バッファ配列設定
			virtual void SetVertexBuffers(IResource* resources[], uint64_t strides[], uint64_t sizes[], uint32_t start, uint32_t count) const override;
			// インデックスバッファ設定
			virtual void SetIndexBuffer(IResource* resource, uint64_t size, IndexFormat format) const override;
			// シーザーレクト配列設定
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const override;
			// ビューポート配列設定
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const override;
			// レンダーターゲット配列設定
			virtual void SetRenderTargets(IResourceView* renderTarget[], uint32_t count, IResourceView* depthStencil) const override;

			virtual void CopyResource(IResource* source, IResource* destination) const override;

			virtual void CopyBuffer(IResource* source, IResource* destination, uint64_t byteSize, uint32_t sourceOffset = 0, uint32_t destinationOffset = 0) const override;

			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const override;

			virtual void Close() const override;

			virtual void Reset() const override;

		};
	}

}