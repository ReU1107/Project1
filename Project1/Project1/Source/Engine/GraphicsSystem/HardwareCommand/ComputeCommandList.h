#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		// GPGPUのみで処理するものだけ貯めることのできるリスト
		class ComputeCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using ComputeCommandListPtr = std::shared_ptr<ComputeCommandList>;
		public:
			// コンストラクタ
			ComputeCommandList();
			// デストラクタ
			virtual ~ComputeCommandList();

			static ComputeCommandListPtr Create(const std::string& name);
		public:
			// デスクリプター設定
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const override;

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

			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const override;

			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const override;

			// リソースコピー
			virtual void CopyResource(Resource* source, Resource* destination) const override;

			virtual void CopyBuffer(Buffer* buffer) const override;
		};
	}
}