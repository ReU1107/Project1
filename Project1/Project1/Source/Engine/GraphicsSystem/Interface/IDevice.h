#pragma once
//#include "../..//IUnknown.h"

namespace Engine
{

	namespace GraphicsSystem 
	{

		// 前方宣言
		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class IRootSignature;
		class IRasterizerPipeline;
		class IRaytracingPipeline;
		class IComputePipeline;

		struct BufferDesc;
		struct TextureDesc;
		struct ResourceViewDesc;
		struct DescriptorHeapDesc;
		struct PipelineDesc;
		struct RaytracingPipelineDesc;
		struct RootSignatureDesc;
		struct RasterizerPipelineDesc;
		struct ComputePipelineDesc;

		class IDevice// : public IUnknown
		{
		public:
			// 仮想デストラクタ
			virtual ~IDevice() {}

			// バッファ作成
			virtual IResource* CreateBuffer(const BufferDesc& desc) const = 0;
			// テクスチャ作成
			virtual IResource* CreateTexture(const TextureDesc& desc) const = 0;

			virtual IResourceView* CreateResourceView(const ResourceViewDesc& desc) const = 0;

			virtual IResourceView* CreateResourceView() const = 0;

			virtual void RecreateResourceView(IResourceView* view, const ResourceViewDesc& desc) const = 0;

			// デスクリプターヒープ()作成
			virtual IDescriptorHeap* CreateDescriptorHeap(const DescriptorHeapDesc& desc) const = 0;

			virtual IRootSignature* CreateRootSignature(const RootSignatureDesc& desc) const = 0;

			virtual IRasterizerPipeline* CreateRasterizerPipeline(const RasterizerPipelineDesc& desc) const = 0;

			virtual IRaytracingPipeline* CreateRaytracingPipeline(const RaytracingPipelineDesc& desc) const = 0;

			virtual IComputePipeline* CreateComputePipeline(const ComputePipelineDesc& desc) const = 0;
		};

	}

}