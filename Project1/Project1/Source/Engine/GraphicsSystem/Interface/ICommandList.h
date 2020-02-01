#pragma once
#include <cstdint>

namespace Engine
{
	struct Rect;
	struct Viewport;

	namespace GraphicsSystem 
	{

		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class IRootSignature;
		class IRasterizerPipeline;
		class IRaytracingPipeline;
		class IComputePipeline;
		class IAccelerationStructure;

		struct RaytracingDispatchDesc;
		struct RasterizerPipelineDesc;
		enum class ResourceStates : uint16_t;
		enum class PrimitiveTopology : uint8_t;
		enum class IndexFormat : uint8_t;

		class ICommandList
		{
		public:
			// 仮想デストラクタ
			virtual ~ICommandList() {}

			virtual void* GetNativeCommandList() const = 0;

			virtual void ClearRenderTarget(IResourceView* renderTargetView, const Rect& rect, float color[4]) const = 0;

			virtual void ClearDepthStencil(IResourceView* depthStencilView, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const = 0;

			virtual void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) const = 0;

			// 
			virtual void BuildBottomLevelAccelerationStructure(IAccelerationStructure* as) const = 0;

			// シーン作成コマンド発行
			virtual void BuildTopLevelAccelerationStructure(IAccelerationStructure* as) const = 0;

			// レイトレーシング実行コマンド発行
			virtual void DispatchRaytracing(const RaytracingDispatchDesc& desc) const = 0;
			// リソースの仕様方法を変更し意図しないアクセスを防ぎます
			virtual void ResourceBarrierTransition(IResource* resources[], uint32_t resourceCount, ResourceStates before, ResourceStates after, uint32_t subResourceCount = -1) const = 0;

			// ここで使用する全てのリソースが入っているデータ設定
			virtual void SetDescriptorHeaps(IDescriptorHeap* descriptorHeaps[], uint32_t heapCount = 1) const = 0;
			// デスクリプターテーブル設定(コンピュートシェーダー)
			virtual void SetComputeDescriptorTable(IResourceView* view, uint32_t parameterIndex) const = 0;
			virtual void SetComputeDescriptorTable(IDescriptorHeap* heap, uint32_t parameterIndex) const = 0;

			// シェーダーリソースビュー設定(コンピュートシェーダー)
			virtual void SetComputeShaderResource(IResource* resource, uint32_t parameterIndex) const = 0;
			// 定数バッファビュー設定(コンピュートシェーダー)
			virtual void SetComputeConstantBuffer(IResource* resource, uint32_t parameterIndex) const = 0;
			// アンオーダードアクセスビュー設定(コンピュートシェーダー)
			virtual void SetComputeUnorderedAccess(IResource* resource, uint32_t parameterIndex) const = 0;

			// 
			virtual void UnorderedAccessBarrier(IResource* resources[], uint32_t resourceCount) const = 0;
			// ルートシグネチャ設定(コンピュート)
			virtual void SetComputeRootSignature(IRootSignature* rootSignature) const = 0;
			// ルートシグネチャ設定(グラフィック)
			virtual void SetGraphicsRootSignature(IRootSignature* rootSignature) const = 0;
			// デスクリプターテーブル設定(グラフィック)
			virtual void SetGraphicsRootDescriptorTable(IResourceView* view, uint32_t index) const = 0;
			// シェーダーリソースビュー設定(グラフィック)
			virtual void SetGraphicsShaderResource(IResource* resource, uint32_t index) const = 0;
			// 定数ビュー設定(グラフィック)
			virtual void SetGraphicsConstantBuffer(IResource* resource, uint32_t index) const = 0;
			// アンオーダードアクセスビュー設定(グラフィック)
			virtual void SetGraphicsUnorderedAccess(IResource* resource, uint32_t index) const = 0;
			// レイトレーシングパイプライン設定
			virtual void SetRaytracingPipeline(IRaytracingPipeline* pipeline) const = 0;
			// ラスタライザーパイプライン設定
			virtual void SetRasterizerPipeline(IRasterizerPipeline* pipeline) const = 0;

			virtual void SetComputePipeline(IComputePipeline* pipeline) const = 0;

			// プリミティブ設定
			virtual void SetPrimitiveTopology(PrimitiveTopology topology) const = 0;
			// 頂点バッファ配列設定
			virtual void SetVertexBuffers(IResource* resource[], uint64_t strides[], uint64_t sizes[], uint32_t start, uint32_t count) const = 0;
			// インデックスバッファ設定
			virtual void SetIndexBuffer(IResource* resource, uint64_t size, IndexFormat format) const = 0;
			// シーザーレクト配列設定
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const = 0;
			// ビューポート配列設定
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const = 0;
			// レンダーターゲット配列設定
			virtual void SetRenderTargets(IResourceView* renderTarget[], uint32_t count, IResourceView* depthStencil) const = 0;

			// リソースコピー
			virtual void CopyResource(IResource* source, IResource* destination) const = 0;

			virtual void CopyBuffer(IResource* source, IResource* destination, uint64_t byteSize, uint32_t sourceOffset, uint32_t destinationOffset) const = 0;

			// 
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const = 0;

			// 
			virtual void Close() const = 0;

			// 
			virtual void Reset() const = 0;

		};

	}
}