#pragma once
#include "..//Interface/IDevice.h"
#include <cstdint>
#include <d3d12.h>
#include <dxgi1_6.h>

namespace Engine 
{
	struct Viewport;
	struct Rect;

	namespace GraphicsSystem 
	{
		class IAdapter;

		struct RaytracingDispatchDesc;
		struct RasterizerPipelineDesc;
		enum class ResourceStates : uint16_t;
		enum class PrimitiveTopology : uint8_t;
		enum class IndexFormat : uint8_t;
		class ICommandList;
		struct CommandListDesc;
		class ICommandQueue;
		struct CommandQueueDesc;

		class IAccelerationStructure;
		struct TopLevelAccelerationStructureDesc;
		struct BottomLevelAccelerationStructureDesc;


		class D3D12Device final : public IDevice
		{
		public:
			// 最終的に持つ変数はこの2つだけにしたい
			ID3D12Device5* m_device;

		public:
			// コンストラクタ
			D3D12Device(uint64_t width, uint64_t height, IAdapter* adapter);
			// デストラクタ
			virtual ~D3D12Device();

		public:
			ID3D12Device5* GetNativeDevice() const { return m_device; }

			// バッファ作成
			virtual IResource* CreateBuffer(const BufferDesc& desc) const override;
			// テクスチャ作成
			virtual IResource* CreateTexture(const TextureDesc& desc) const override;

			// リソースビュー作成
			virtual IResourceView* CreateResourceView(const ResourceViewDesc& desc) const override;

			virtual IResourceView* CreateResourceView() const override;

			IResource* CreateCopyableResource(IResource* resource) const;

			// リソースビュー作り直し
			virtual void RecreateResourceView(IResourceView* view, const ResourceViewDesc& desc) const override;

			// デスクリプターヒープ()作成
			virtual IDescriptorHeap* CreateDescriptorHeap(const DescriptorHeapDesc& desc) const override;

			// 
			IAccelerationStructure* CreateTopLevelAccelerationStructure() const;

			// 
			void RecreateTopLevelAccelerationStructure(IAccelerationStructure* as, const TopLevelAccelerationStructureDesc& desc) const;

			// 
			IAccelerationStructure* CreateBottomLevelAccelerationStrcture() const;

			// 
			void RecreateBottomLevelAccelerationStructure(IAccelerationStructure* as, const BottomLevelAccelerationStructureDesc& desc) const;

			// ルートシグネチャ作成
			virtual IRootSignature* CreateRootSignature(const RootSignatureDesc& desc) const override;
			
			// ラスタライザーパイプライン作成
			virtual IRasterizerPipeline* CreateRasterizerPipeline(const RasterizerPipelineDesc& desc) const override;

			// レイトレーシングパイプライン作成
			virtual IRaytracingPipeline* CreateRaytracingPipeline(const RaytracingPipelineDesc& desc) const override;
			
			// コンピュートパイプライン作成
			virtual IComputePipeline* CreateComputePipeline(const ComputePipelineDesc& desc) const override;

			// コマンドリスト作成
			ICommandList* CreateCommandList(const CommandListDesc& desc);
			// コマンドキュー作成
			ICommandQueue* CreateCommandQueue(const CommandQueueDesc& desc);

		private:
			// 低レベルリソース作成
			ID3D12Resource1* CreateNativeResource(const D3D12_HEAP_PROPERTIES& properties, D3D12_HEAP_FLAGS flags, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES states, D3D12_CLEAR_VALUE* value = nullptr) const;

			ID3D12Resource1* CreateNativeBuffer(uint64_t size, D3D12_RESOURCE_FLAGS resourceFlags, D3D12_RESOURCE_STATES resourceStates, D3D12_HEAP_TYPE heapType = D3D12_HEAP_TYPE_DEFAULT, DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN) const;
		
			void CreateShaderResourceView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle, uint32_t stride, bool raw, bool raytracing = false) const;

			void CreateRenderTargetView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

			void CreateDepthStencilView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

			void CreateUnorderedAccessView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle, uint32_t stride, bool raw) const;

			void CreateConstantBufferView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;
	
			ID3DBlob* SerializeRootSignature(const D3D12_ROOT_SIGNATURE_DESC& desc) const;

			ID3D12RootSignature* CreateNativeRootSignature(ID3DBlob* blob) const;

			//DeclareIUnknownInterfaces();
		};

	}

}