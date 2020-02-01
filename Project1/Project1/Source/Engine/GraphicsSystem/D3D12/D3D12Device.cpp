#include "D3D12Device.h"
//#include <d3d12.h>
//#include <dxgi1_6.h>
#include <cassert>
#include <vector>
#include "D3D12Resource.h"
#include "..//Description/Include.h"
#include "..//Enumerations/Include.h"
#include "../../Utility/EnumOperator.h"
#include "D3D12CommandQueue.h"
#include "D3D12ComputePipeline.h"
#include "D3D12Desc.h"
#include "D3D12Enumeration.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12GraphicsPipeline.h"
#include "D3D12RaytracingPipeline.h"
#include "D3D12Resource.h"
#include "D3D12ResourceView.h"
#include "D3D12RootSignature.h"
#include "D3D12Shader.h"
#include "D3D12RaytracingPipeline.h"
#include "D3D12RasterizerPipeline.h"
#include "D3D12CommandList.h"
#include "D3D12CommandQueue.h"
#include "D3D12TopLevelAccelerationStructure.h"
#include "D3D12BottomLevelAccelerationStructure.h"
#include "..//..//String/StringHelper.h"
#include "..//..//Math/Rect.h"
#include "..//..//Math/Viewport.h"

#include "..//DXGI/DXGIAdapter.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

// https://shikihuiku.wordpress.com/2015/03/31/about_3d12_heap_type_upload/

namespace Engine 
{
	namespace GraphicsSystem 
	{
		static IResourceView* v = nullptr;

		D3D12Device::D3D12Device(uint64_t width, uint64_t height, IAdapter* adapter)
			: m_device(nullptr)
		{
			HRESULT hr;
#if _DEBUG
			ID3D12Debug3* debug = nullptr;
			hr = D3D12GetDebugInterface(__uuidof(ID3D12Debug3), (void**)& debug);

			debug->EnableDebugLayer();
			debug->Release();
			//debug->SetEnableGPUBasedValidation(true);
#endif
			ID3D12Device5* device = nullptr;

			hr = D3D12CreateDevice(((DXGIAdapter*)adapter)->m_nativeAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
			m_device = device;
			// この二行の動作をデバイス作成後に行うとエラーになるため注意
			//UUID experimentalFeatures[] = { D3D12ExperimentalShaderModels };
			//hr = D3D12EnableExperimentalFeatures(1, experimentalFeatures, nullptr, nullptr);

			D3D12_FEATURE_DATA_D3D12_OPTIONS5 data = {};
			hr = m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &data, sizeof(data));

			if (data.RaytracingTier == D3D12_RAYTRACING_TIER_NOT_SUPPORTED) {
				MessageBox(nullptr, "RTXを使用してください", "エラー", MB_OK);
				return;
			}
		}

		D3D12Device::~D3D12Device()
		{
			m_device->Release();
		}

		IResource* D3D12Device::CreateBuffer(const BufferDesc& desc) const
		{
			D3D12_HEAP_TYPE heapType = desc.isDynamic ? D3D12_HEAP_TYPE_UPLOAD : D3D12_HEAP_TYPE_DEFAULT;
			D3D12_RESOURCE_FLAGS resourceFlags = D3D12_RESOURCE_FLAG_NONE;
			uint64_t size = desc.size;

			if ((desc.flags & ResourceFlags::AllowUnorderedAccess) != 0)
			{
				heapType = D3D12_HEAP_TYPE_DEFAULT;
				resourceFlags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			}

			D3D12_RESOURCE_STATES resourceStates = D3D12_RESOURCE_STATE_COMMON;

			resourceStates |= D3D12_RESOURCE_STATE_GENERIC_READ;
			ID3D12Resource1* nativeResource = CreateNativeBuffer(size, resourceFlags, resourceStates, heapType);

			D3D12Resource* resource = new D3D12Resource();
			resource->m_nativeResource = nativeResource;

			return resource;
		}

		IResource* D3D12Device::CreateTexture(const TextureDesc& desc) const
		{
			D3D12_HEAP_PROPERTIES prop = {};
			prop.Type = D3D12_HEAP_TYPE_DEFAULT;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 1;
			prop.VisibleNodeMask = 1;

			D3D12_RESOURCE_DIMENSION dimension = D3D12ResourceDimension(desc.dimension);

			D3D12_RESOURCE_FLAGS resourceFlags = D3D12ResourceFlags(desc.flags);

			DXGI_FORMAT format = DXGIFormat(desc.format);

			D3D12_RESOURCE_DESC nativeDesc = {};
			nativeDesc.Dimension = dimension;
			nativeDesc.Alignment = 0;
			nativeDesc.Width = desc.width;
			nativeDesc.Height = desc.height;
			nativeDesc.DepthOrArraySize = desc.arrayCount;
			nativeDesc.MipLevels = desc.mipLevel;
			nativeDesc.Format = format;
			nativeDesc.SampleDesc.Count = desc.multiSampleCount;
			nativeDesc.SampleDesc.Quality = desc.multiSampleQuality;
			nativeDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			nativeDesc.Flags = resourceFlags;

			D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS;
			D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS feature = {};
			feature.Format = format;
			feature.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
			feature.NumQualityLevels = desc.multiSampleQuality;
			feature.SampleCount = desc.multiSampleCount;

			auto hr = m_device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &feature, sizeof(feature));

			D3D12_RESOURCE_STATES resourceStates = D3D12ResourceStates(desc.states);

			ID3D12Resource1* nativeResource = nullptr;

			D3D12_CLEAR_VALUE clearValue = {};
			clearValue.Format = format;

			if ((desc.flags & ResourceFlags::AllowDepthStencil) != 0)
			{
				clearValue.DepthStencil.Depth = desc.clearValue.depth;
				clearValue.DepthStencil.Stencil = desc.clearValue.stencil;
				auto hr = m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &nativeDesc, resourceStates, &clearValue, IID_PPV_ARGS(&nativeResource));
				if (FAILED(hr))
				{
					assert(!"テクスチャの作成に失敗しました");
					return nullptr;
				}
			}
			else if ((desc.flags & ResourceFlags::AllowRenderTarget) != 0)
			{
				clearValue.Color[0] = desc.clearValue.color[0];
				clearValue.Color[1] = desc.clearValue.color[1];
				clearValue.Color[2] = desc.clearValue.color[2];
				clearValue.Color[3] = desc.clearValue.color[3];
				auto hr = m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &nativeDesc, resourceStates, &clearValue, IID_PPV_ARGS(&nativeResource));
				if (FAILED(hr))
				{
					assert(!"テクスチャの作成に失敗しました");
					return nullptr;
				}
			}
			else
			{
				auto hr = m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &nativeDesc, resourceStates, nullptr, IID_PPV_ARGS(&nativeResource));
				if (FAILED(hr))
				{
					assert(!"テクスチャの作成に失敗しました");
					return nullptr;
				}
			}

			D3D12Resource* resource = new D3D12Resource();
			resource->m_nativeResource = nativeResource;

			return resource;
		}

		IResourceView* D3D12Device::CreateResourceView(const ResourceViewDesc& desc) const
		{
			auto descriptor = (D3D12DescriptorHeap*)desc.descriptorHeap;

			auto type = D3D12DescriptorHeapType(descriptor->m_type);
			
			auto* descriptorHeap = descriptor->m_native;
			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
			D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
			// タイプに基づいたサイズ取得
			uint32_t size = m_device->GetDescriptorHandleIncrementSize(type);
			uint32_t index = descriptor->m_index++;
			uint64_t stride = (uint64_t)size * index;

			// 作成済みの場所の次から作成する
			cpuHandle.ptr += stride;
			gpuHandle.ptr += stride;
			ID3D12Resource1* nativeResource = (ID3D12Resource1*)desc.resource->GetNativeResource();

			switch (desc.type)
			{
			case ResourceViewType::ShaderResource:
				CreateShaderResourceView(nativeResource, cpuHandle, desc.stride, desc.isRaw);
				break;
			case ResourceViewType::RenderTarget:
				CreateRenderTargetView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::DepthStencil:
				CreateDepthStencilView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::UnorderedAccess:
				CreateUnorderedAccessView(nativeResource, cpuHandle, desc.stride, desc.isRaw);
				break;
			case ResourceViewType::ConstantBuffer:
				CreateConstantBufferView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::Raytracing:
				CreateShaderResourceView(nativeResource, cpuHandle, desc.stride, desc.isRaw, true);
				break;
			default:
				break;
			}

			D3D12ResourceView* resourceView = new D3D12ResourceView();
			resourceView->m_cpuHandle = cpuHandle;
			resourceView->m_gpuHandle = gpuHandle;
			resourceView->m_index = index;

			return resourceView;
		}

		IResourceView* D3D12Device::CreateResourceView() const
		{
			D3D12ResourceView* resourceView = new D3D12ResourceView();
			return resourceView;
		}

		IResource* D3D12Device::CreateCopyableResource(IResource* resource) const
		{
			ID3D12Resource1* nativeResource = (ID3D12Resource1*)resource->GetNativeResource();
			D3D12_RESOURCE_DESC desc = nativeResource->GetDesc();

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
			uint64_t totalBytes = 0;
			uint32_t rowCount = 0;
			uint64_t byte = 0;
			m_device->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &rowCount, &byte, &totalBytes);

			// コピー元を作成する
			desc = {};
			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Width = totalBytes;
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.SampleDesc.Count = 1;
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			// コピー元にデータを入れる
			D3D12_HEAP_PROPERTIES properties = {};
			D3D12_HEAP_FLAGS flags = {};
			nativeResource->GetHeapProperties(&properties, &flags);
			properties = {};
			properties.Type = D3D12_HEAP_TYPE_UPLOAD;
			ID3D12Resource1* copyNativeResource = CreateNativeResource(properties, flags, desc, D3D12_RESOURCE_STATE_GENERIC_READ);
			
			D3D12Resource* copyResource = new D3D12Resource();
			copyResource->m_nativeResource = copyNativeResource;

			return copyResource;
		}

		void D3D12Device::RecreateResourceView(IResourceView* resourceView, const ResourceViewDesc& desc) const
		{
			auto descriptor = (D3D12DescriptorHeap*)desc.descriptorHeap;

			auto type = D3D12DescriptorHeapType(descriptor->m_type);

			auto* descriptorHeap = descriptor->m_native;
			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
			D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
			// タイプに基づいたサイズ取得
			uint32_t size = m_device->GetDescriptorHandleIncrementSize(type);
			uint32_t index = descriptor->m_index++;
			uint64_t stride = (uint64_t)size * index;

			// 作成済みの場所の次から作成する
			cpuHandle.ptr += stride;
			gpuHandle.ptr += stride;
			ID3D12Resource1* nativeResource = (ID3D12Resource1*)desc.resource->GetNativeResource();

			switch (desc.type)
			{
			case ResourceViewType::ShaderResource:
				CreateShaderResourceView(nativeResource, cpuHandle, desc.stride, desc.isRaw);
				break;
			case ResourceViewType::RenderTarget:
				CreateRenderTargetView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::DepthStencil:
				CreateDepthStencilView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::UnorderedAccess:
				CreateUnorderedAccessView(nativeResource, cpuHandle, desc.stride, desc.isRaw);
				break;
			case ResourceViewType::ConstantBuffer:
				CreateConstantBufferView(nativeResource, cpuHandle);
				break;
			case ResourceViewType::Raytracing:
				CreateShaderResourceView(nativeResource, cpuHandle, desc.stride, desc.isRaw, true);
				break;
			default:
				break;
			}

			((D3D12ResourceView*)resourceView)->m_cpuHandle = cpuHandle;
			((D3D12ResourceView*)resourceView)->m_gpuHandle = gpuHandle;
			((D3D12ResourceView*)resourceView)->m_index = index;
		}

		IRaytracingPipeline* D3D12Device::CreateRaytracingPipeline(const RaytracingPipelineDesc& desc) const
		{
			std::vector<D3D12_STATE_SUBOBJECT> subObjects(desc.parameterCount);

			std::vector<D3D12_RAYTRACING_PIPELINE_CONFIG> pipelineConfigs(desc.parameterCount);
			std::vector<D3D12_RAYTRACING_SHADER_CONFIG> shaderConfigs(desc.parameterCount);
			std::vector<D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION> associations(desc.parameterCount);
			std::vector<D3D12_DXIL_LIBRARY_DESC> libraries(desc.parameterCount);
			std::vector<D3D12_HIT_GROUP_DESC> hitGroups(desc.parameterCount);
			std::vector<ID3D12RootSignature*> rootSignatures(desc.parameterCount);

			for (uint32_t i = 0; i < desc.parameterCount; i++)
			{
				auto& parameter = desc.parameters[i];
				auto& subObject = subObjects[i];
				subObject = {};
				switch (parameter.parameterType)
				{
				case RaytracingPipelineParameterType::PipelineConfig:
				{
					D3D12_RAYTRACING_PIPELINE_CONFIG pipelineConfig = {};
					pipelineConfig.MaxTraceRecursionDepth = parameter.pipelineConfig.raytraceMaxCount;
					pipelineConfigs[i] = pipelineConfig;
					subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG;
					subObject.pDesc = &(pipelineConfigs[i]);

				}	break;
				case RaytracingPipelineParameterType::ShaderConfig:
				{
					D3D12_RAYTRACING_SHADER_CONFIG shaderConfig = {};
					shaderConfig.MaxAttributeSizeInBytes = parameter.shaderConfig.attributeSize;
					shaderConfig.MaxPayloadSizeInBytes = parameter.shaderConfig.payloadSize;
					shaderConfigs[i] = shaderConfig;
					subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_SHADER_CONFIG;
					subObject.pDesc = &(shaderConfigs[i]);

				}	break;
				case RaytracingPipelineParameterType::Association:
				{

					uint32_t associationIndex = parameter.association.index;
					D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION association = D3D12SubObjectToExportAssociation(parameter.association, &(subObjects[associationIndex]));
					associations[i] = association;
					subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION;
					subObject.pDesc = &(associations[i]);

				}	break;
				case RaytracingPipelineParameterType::ShaderLibrary:
				{
					D3D12_DXIL_LIBRARY_DESC library = D3D12DXILLibrary(parameter.shaderLibrary);
					libraries[i] = library;
					subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
					subObject.pDesc = &(libraries[i]);
				}	break;
				case RaytracingPipelineParameterType::Signature:
				{
					ID3D12RootSignature* rootSignature = nullptr;
					rootSignature = (ID3D12RootSignature*)parameter.signature.rootSignature->GetNativeSignature();
					rootSignatures[i] = rootSignature;

					switch (parameter.signature.type)
					{
					case RootSignatureType::Global:
					{
						subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE;
						subObject.pDesc = &(rootSignatures[i]);
					}	break;
					case RootSignatureType::Local:
					{
						subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE;
						subObject.pDesc = &(rootSignatures[i]);
					}	break;
					default:
						break;
					}
				}	break;
				case RaytracingPipelineParameterType::HitGroup:
				{
					D3D12_HIT_GROUP_DESC hitGroup = D3D12HitGroupDesc(parameter.hitGroup);
					hitGroups[i] = hitGroup;

					subObject.Type = D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP;
					subObject.pDesc = &(hitGroups[i]);

				}	break;
				default:
					break;
				}

			}

			D3D12_STATE_OBJECT_DESC nativeDesc = {};
			nativeDesc.Type = D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE;
			nativeDesc.NumSubobjects = (UINT)subObjects.size();
			nativeDesc.pSubobjects = subObjects.data();

			ID3D12StateObject* stateObject = nullptr;

			auto hr = m_device->CreateStateObject(&nativeDesc, IID_PPV_ARGS(&stateObject));
			if (FAILED(hr)) {
				assert(!"レイトレーシングパイプラインオブジェクトの作成に失敗しました");
			}

			ID3D12StateObjectProperties* properties = nullptr;
			stateObject->QueryInterface(IID_PPV_ARGS(&properties));

			D3D12RaytracingPipeline* pipeline = new D3D12RaytracingPipeline();
			pipeline->m_native = stateObject;
			pipeline->m_properties = properties;

			return pipeline;
		}

		IComputePipeline* D3D12Device::CreateComputePipeline(const ComputePipelineDesc& desc) const
		{
			D3D12_COMPUTE_PIPELINE_STATE_DESC nativeDesc = {};
			nativeDesc.NodeMask = desc.nodeMask;
			nativeDesc.pRootSignature = (ID3D12RootSignature*)desc.rootSignature->GetNativeSignature();
			nativeDesc.CS.pShaderBytecode = desc.computeShader->GetBuffer();
			nativeDesc.CS.BytecodeLength = desc.computeShader->GetSize();
//#if _DEBUG
//			nativeDesc.Flags = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG;
//#endif

			ID3D12PipelineState* pipelineState = nullptr;
			auto hr = m_device->CreateComputePipelineState(&nativeDesc, IID_PPV_ARGS(&pipelineState));
			if (FAILED(hr))
			{
				assert(!"コンピュートパイプラインの作成に失敗しました");
			}

			D3D12ComputePipeline* pipeline = new D3D12ComputePipeline();
			pipeline->m_native = pipelineState;

			return pipeline;
		}

		ICommandList* D3D12Device::CreateCommandList(const CommandListDesc& desc)
		{
			D3D12_COMMAND_LIST_TYPE type = D3D12CommandListType(desc.type);
			ID3D12CommandAllocator* allocator = nullptr;
			auto hr = m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&allocator));
			if (FAILED(hr))
			{
				assert(!"コマンドアロケーターの作成に失敗しました");
			}

			ID3D12GraphicsCommandList5* nativeList = nullptr;
			hr = m_device->CreateCommandList1(0, type, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&nativeList));
			if (FAILED(hr))
			{
				assert(!"コマンドリストの作成に失敗しました");
			}
			hr = allocator->Reset();
			hr = nativeList->Reset(allocator, nullptr);

			D3D12CommandList* list = new D3D12CommandList();
			list->m_nativeList = nativeList;
			list->m_nativeAllocator = allocator;
			return list;
		}

		ICommandQueue* D3D12Device::CreateCommandQueue(const CommandQueueDesc& desc)
		{
			ID3D12CommandQueue* nativeQueue = nullptr;
			D3D12_COMMAND_QUEUE_DESC nativeDesc = {};
			nativeDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			nativeDesc.NodeMask = 0;
			nativeDesc.Priority = D3D12CommandQueuePriority(desc.priority);
			nativeDesc.Type = D3D12CommandListType(desc.type);;
			auto hr = m_device->CreateCommandQueue(&nativeDesc, IID_PPV_ARGS(&nativeQueue));
			if (FAILED(hr))
			{
				assert(!"コマンドキューの作成に失敗しました");
			}

			ID3D12Fence1* fence = nullptr;
			m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
			HANDLE handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);

			D3D12CommandQueue* queue = new D3D12CommandQueue();
			queue->m_nativeQueue = nativeQueue;
			queue->m_fence = fence;
			queue->m_handle = handle;

			return queue;
		}

		IDescriptorHeap* D3D12Device::CreateDescriptorHeap(const DescriptorHeapDesc& desc) const
		{
			D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12DescriptorHeapType(desc.type);

			D3D12_DESCRIPTOR_HEAP_DESC nativeDesc = {};
			nativeDesc.NumDescriptors = desc.count;
			nativeDesc.Type = type;
			nativeDesc.Flags = desc.shaderAccess ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			nativeDesc.NodeMask = 0;

			ID3D12DescriptorHeap* nativeHeap = nullptr;
			if (FAILED(m_device->CreateDescriptorHeap(&nativeDesc, IID_PPV_ARGS(&nativeHeap)))) {
				assert(!"デスクリプターヒープの作成に失敗しました");
				return nullptr;
			}

			D3D12DescriptorHeap* descriptorHeap = new D3D12DescriptorHeap();
			descriptorHeap->m_native = nativeHeap;
			descriptorHeap->m_count = desc.count;
			descriptorHeap->m_type = desc.type;

			return descriptorHeap;
		}

		IAccelerationStructure* D3D12Device::CreateTopLevelAccelerationStructure() const
		{
			D3D12TopLevelAccelerationStructure* as = new D3D12TopLevelAccelerationStructure();
			return as;
		}

		void D3D12Device::RecreateTopLevelAccelerationStructure(IAccelerationStructure* as, const TopLevelAccelerationStructureDesc& desc) const
		{
			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs = {};
			inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
			inputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE;
			inputs.NumDescs = desc.bottomCount;
			inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;

			D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO preInfomation;
			m_device->GetRaytracingAccelerationStructurePrebuildInfo(&inputs, &preInfomation);

			ID3D12Resource1* result = nullptr;
			ID3D12Resource1* scratch = nullptr;
			ID3D12Resource1* update = nullptr;
			ID3D12Resource1* instanceBuffer = nullptr;

			uint64_t size = preInfomation.ScratchDataSizeInBytes;

			scratch = CreateNativeBuffer(size, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

			size = preInfomation.ResultDataMaxSizeInBytes;
			result = CreateNativeBuffer(size, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);

			size = sizeof(D3D12_RAYTRACING_INSTANCE_DESC) * desc.bottomCount;
			instanceBuffer = CreateNativeBuffer(size, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);

			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC asDesc = {};
			asDesc.Inputs = inputs;
			asDesc.Inputs.InstanceDescs = instanceBuffer->GetGPUVirtualAddress();
			asDesc.DestAccelerationStructureData = result->GetGPUVirtualAddress();
			asDesc.ScratchAccelerationStructureData = scratch->GetGPUVirtualAddress();

			D3D12TopLevelAccelerationStructure* toplevel = (D3D12TopLevelAccelerationStructure*)as;
			toplevel->m_instanceBuffer = instanceBuffer;
			toplevel->m_result = result;
			toplevel->m_scratch = scratch;
			toplevel->m_desc = asDesc;
		}

		IAccelerationStructure* D3D12Device::CreateBottomLevelAccelerationStrcture() const
		{
			D3D12BottomLevelAccelerationStructure* as = new D3D12BottomLevelAccelerationStructure();
			return as;
		}

		void D3D12Device::RecreateBottomLevelAccelerationStructure(IAccelerationStructure* as, const BottomLevelAccelerationStructureDesc& desc) const
		{
			std::vector<D3D12_RAYTRACING_GEOMETRY_DESC> nativeDescs(desc.subCount);
			for (uint32_t i = 0; i < desc.subCount; ++i)
			{

				auto& subDesc = desc.subDescs[i];
				auto& nativeDesc = nativeDescs[i];
				nativeDesc.Flags = D3D12RaytracingGeometryFlags(desc.flags);

				ID3D12Resource* unionBuffer = nullptr;
				ID3D12Resource* indexBuffer = nullptr;
				ID3D12Resource* constantBuffer = nullptr;
				DXGI_FORMAT vertexFormat;
				DXGI_FORMAT indexFormat;

				switch (subDesc.type)
				{
				case BottomLevelType::Traiangles:

					// 頂点バッファがないのはダメ
					assert(subDesc.vertexBuffer);

					vertexFormat = DXGIVertexFormat(subDesc.vertexFormat);

					nativeDesc.Type = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;
					unionBuffer = (ID3D12Resource*)subDesc.vertexBuffer->GetNativeResource();
					nativeDesc.Triangles.VertexBuffer.StartAddress = unionBuffer->GetGPUVirtualAddress();
					nativeDesc.Triangles.VertexBuffer.StrideInBytes = subDesc.vertexStride;
					nativeDesc.Triangles.VertexFormat = vertexFormat;
					nativeDesc.Triangles.VertexCount = subDesc.vertexCount;

					if (subDesc.indexBuffer)
					{
						indexFormat = DXGIIndexFormat(subDesc.indexFormat);

						indexBuffer = (ID3D12Resource*)subDesc.indexBuffer->GetNativeResource();
						nativeDesc.Triangles.IndexBuffer = indexBuffer->GetGPUVirtualAddress();
						nativeDesc.Triangles.IndexCount = subDesc.indexCount;
						nativeDesc.Triangles.IndexFormat = indexFormat;
					}

					break;
				case BottomLevelType::Procedural:

					// 頂点バッファがないのはダメ
					assert(subDesc.aabbBuffer);

					unionBuffer = (ID3D12Resource*)subDesc.aabbBuffer->GetNativeResource();
					nativeDesc.Type = D3D12_RAYTRACING_GEOMETRY_TYPE_PROCEDURAL_PRIMITIVE_AABBS;
					nativeDesc.AABBs.AABBCount = subDesc.aabbCount;
					nativeDesc.AABBs.AABBs.StartAddress = unionBuffer->GetGPUVirtualAddress();
					nativeDesc.AABBs.AABBs.StrideInBytes = sizeof(D3D12_RAYTRACING_AABB);
					break;
				default:
					break;
				}
				if (subDesc.constantBuffer)
				{
					constantBuffer = (ID3D12Resource*)subDesc.constantBuffer->GetNativeResource();
					nativeDesc.Triangles.Transform3x4 = constantBuffer->GetGPUVirtualAddress();
				}

			}

			D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS inputsFlags = D3D12RaytracingAccelerationBuildFlags(desc.buildFlags);

			// バッファを作成するのに必要なサイズ取得
			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs = {};
			inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
			inputs.Flags = inputsFlags;
			inputs.NumDescs = desc.subCount;
			inputs.pGeometryDescs = nativeDescs.data();
			inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;

			D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO preInfo = {};
			m_device->GetRaytracingAccelerationStructurePrebuildInfo(&inputs, &preInfo);

			ID3D12Resource1* resultBuffer = nullptr;
			ID3D12Resource1* scratchBuffer = nullptr;
			ID3D12Resource1* updateBuffer = nullptr;

			{
				// 構築に必要なバッファ
				scratchBuffer = CreateNativeBuffer(preInfo.ScratchDataSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

				// 構築後を保持するバッファ
				resultBuffer = CreateNativeBuffer(preInfo.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);

				// 頂点を更新する際に必要なバッファ
				if (preInfo.UpdateScratchDataSizeInBytes > 0)
				{
					updateBuffer = CreateNativeBuffer(preInfo.UpdateScratchDataSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COMMON);
				}

			}

			D3D12BottomLevelAccelerationStructure* acceleration = (D3D12BottomLevelAccelerationStructure*)as;
			acceleration->m_result = resultBuffer;
			acceleration->m_scratch = scratchBuffer;
			acceleration->m_update = updateBuffer;
			acceleration->m_nativeDescs = std::move(nativeDescs);
			acceleration->m_flags = inputsFlags;
		}

		D3D12_STATIC_SAMPLER_DESC StaticSamplerDesc()
		{
			static D3D12_STATIC_SAMPLER_DESC desc = {};
			desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			desc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			desc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
			desc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			desc.MaxAnisotropy = 0;
			desc.MaxLOD = 0.0f;
			desc.MinLOD = 0.0f;
			desc.MipLODBias = 0.0f;

			desc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			desc.ShaderRegister = 0;
			desc.RegisterSpace = 0;

			return desc;
		}

		IRootSignature* D3D12Device::CreateRootSignature(const RootSignatureDesc& desc) const
		{
			D3D12RootSignature* rootSignature = new D3D12RootSignature();
			ID3DBlob* blob = nullptr;

			if (desc.isShader)
			{
				//auto a = desc.shader->GetBuffer();
				//auto b = desc.shader->GetSize();
				//auto hr = D3DGetBlobPart(a, b, D3D_BLOB_ROOT_SIGNATURE, 0, &blob);
				//hr = hr;
			}
			else
			{
				ShaderResourceLayoutDesc* layouts = desc.layouts;
				uint32_t layoutCount = desc.layoutCount;

				std::vector<D3D12_ROOT_PARAMETER> parameters(layoutCount);
				std::vector<D3D12_DESCRIPTOR_RANGE*> rangeArray;

				for (uint32_t i = 0; i < layoutCount; i++) {
					auto& layout = layouts[i];
					auto& parameter = parameters[i];

					switch (layout.layoutType)
					{
					case ShaderResourceLayoutType::DescriptorTable:
					{
						parameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
						D3D12_DESCRIPTOR_RANGE* ranges = new D3D12_DESCRIPTOR_RANGE[layout.descriptorTable.parameterCount];

						for (uint32_t j = 0; j < layout.descriptorTable.parameterCount; j++) {
							ranges[j] = D3D12DescriptorRange(layout.descriptorTable.parameters[j]);
						}
						rangeArray.push_back(ranges);
						parameter.DescriptorTable.pDescriptorRanges = ranges;
						parameter.DescriptorTable.NumDescriptorRanges = layout.descriptorTable.parameterCount;
					}
					break;
					case ShaderResourceLayoutType::Constants:
						parameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
						parameter.Constants = D3D12RootConstans(layout.constans);
						break;
					case ShaderResourceLayoutType::Descriptor:

						parameter.ParameterType = D3D12RootParamerterType(layout.descriptor.type);
						parameter.Descriptor.ShaderRegister = layout.descriptor.index;
						parameter.Descriptor.RegisterSpace = layout.descriptor.space;

						break;
					default:
						assert(!"レイアウトのタイプがおかしいです");
						break;
					}
					parameter.ShaderVisibility = D3D12ShaderVisibiliy(layout.shaderType);

				}
				D3D12_STATIC_SAMPLER_DESC staticSmpler = StaticSamplerDesc();

				D3D12_ROOT_SIGNATURE_DESC nativeDesc = {};
				nativeDesc.Flags = D3D12RootSignatureFlags(desc.flags);
				nativeDesc.NumParameters = (UINT)parameters.size();
				nativeDesc.pParameters = parameters.data();
				if (desc.staticSampler) 
				{
					nativeDesc.pStaticSamplers = &staticSmpler;
					nativeDesc.NumStaticSamplers = 1;
				}
				blob = SerializeRootSignature(nativeDesc);
				for (auto& range : rangeArray)
				{
					delete range;
				}
			}
			ID3D12RootSignature* nativeSignature = CreateNativeRootSignature(blob);
			rootSignature->m_native = nativeSignature;

			return rootSignature;
		}

		IRasterizerPipeline* D3D12Device::CreateRasterizerPipeline(const RasterizerPipelineDesc& desc) const
		{
			D3D12_GRAPHICS_PIPELINE_STATE_DESC nativeDesc = {};
			nativeDesc.InputLayout = D3D12InputLayoutDesc(desc.inputLayout);
			nativeDesc.pRootSignature = (ID3D12RootSignature*)desc.rootSignature->GetNativeSignature();
			IShader* vertexShader = desc.vertexShader;
			if (vertexShader)
			{
				nativeDesc.VS.pShaderBytecode = vertexShader->GetBuffer();
				nativeDesc.VS.BytecodeLength = vertexShader->GetSize();
			}
			IShader* pixelShader = desc.pixelShader;
			if (pixelShader)
			{
				nativeDesc.PS.pShaderBytecode = pixelShader->GetBuffer();
				nativeDesc.PS.BytecodeLength = pixelShader->GetSize();
			}
			IShader* domainShader = desc.domainShader;
			if (domainShader)
			{
				nativeDesc.DS.pShaderBytecode = domainShader->GetBuffer();
				nativeDesc.DS.BytecodeLength = domainShader->GetSize();
			}
			IShader* hullShader = desc.hullShader;
			if (hullShader)
			{
				nativeDesc.HS.pShaderBytecode = hullShader->GetBuffer();
				nativeDesc.HS.BytecodeLength = hullShader->GetSize();
			}
			IShader* geometryShader = desc.geometryShader;
			if (geometryShader)
			{
				nativeDesc.GS.pShaderBytecode = geometryShader->GetBuffer();
				nativeDesc.GS.BytecodeLength = geometryShader->GetSize();
			}
			nativeDesc.RasterizerState = D3D12RasterizerDesc(desc.rasterizerState);
			nativeDesc.BlendState = D3D12BlendDesc(desc.blendState);
			nativeDesc.DepthStencilState = D3D12DepthStencilDesc(desc.depthStencil);
			nativeDesc.SampleMask = desc.sampleMask;
			nativeDesc.SampleDesc.Count = desc.sampleCount;
			nativeDesc.SampleDesc.Quality = desc.sampleQuality;
			nativeDesc.PrimitiveTopologyType = D3D12PrimitiveTopologyType(desc.topology);
			nativeDesc.NumRenderTargets = desc.renderTargetCount;
			for (uint32_t i = 0; i < desc.renderTargetCount; ++i)
			{
				nativeDesc.RTVFormats[i] = DXGIFormat(desc.renderTargetFormats[i]);
			}

			nativeDesc.DSVFormat = DXGIFormat(desc.depthStencilFormat);

//#if _DEBUG
//			nativeDesc.Flags = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG;
//#endif

			ID3D12PipelineState* pipelineState = nullptr;

			auto hr = m_device->CreateGraphicsPipelineState(&nativeDesc, IID_PPV_ARGS(&pipelineState));
			if (FAILED(hr))
			{
				assert(!"ラスタライザーパイプラインオブジェクトの作成に失敗しました");
			}
			D3D12RasterizerPipeline* pipeline = new D3D12RasterizerPipeline();
			pipeline->m_native = pipelineState;

			return pipeline;
		}

		ID3D12Resource1* D3D12Device::CreateNativeResource(const D3D12_HEAP_PROPERTIES& properties, D3D12_HEAP_FLAGS flags, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES states, D3D12_CLEAR_VALUE* value) const
		{
			ID3D12Resource1* resource = nullptr;
			auto hr = m_device->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &desc, states, value, IID_PPV_ARGS(&resource));
			if (FAILED(hr)) {
				assert(!"リソースの作成に失敗しました");
				return nullptr;
			}
			return resource;
		}

		ID3D12Resource1* D3D12Device::CreateNativeBuffer(uint64_t size, D3D12_RESOURCE_FLAGS resourceFlags, D3D12_RESOURCE_STATES resourceStates, D3D12_HEAP_TYPE heapType, DXGI_FORMAT format) const
		{
			D3D12_HEAP_PROPERTIES properties = {};
			properties.Type = heapType;
			properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			properties.CreationNodeMask = 1;
			properties.VisibleNodeMask = 1;

			D3D12_RESOURCE_DESC resourceDesc = {};
			resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resourceDesc.Alignment = 0;
			resourceDesc.Width = size;
			resourceDesc.Height = 1;
			resourceDesc.DepthOrArraySize = 1;
			resourceDesc.MipLevels = 1;
			resourceDesc.Format = format;
			resourceDesc.SampleDesc.Count = 1;
			resourceDesc.SampleDesc.Quality = 0;
			resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			resourceDesc.Flags = resourceFlags;

			return CreateNativeResource(
				properties,
				D3D12_HEAP_FLAG_NONE,
				resourceDesc,
				resourceStates
			);
		}

		void D3D12Device::CreateShaderResourceView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle, uint32_t stride, bool raw, bool raytracing) const
		{
			auto resourceDesc = resource->GetDesc();

			D3D12_SHADER_RESOURCE_VIEW_DESC nativeDesc = {};
			nativeDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			if (raytracing)
			{
				nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
				nativeDesc.RaytracingAccelerationStructure.Location = resource->GetGPUVirtualAddress();
				resource = nullptr;
			}
			else
			{
				// 深度値用をシェーダーリソースとして使用する場合
				switch (resourceDesc.Format)
				{
				case DXGI_FORMAT_D32_FLOAT:
					nativeDesc.Format = DXGI_FORMAT_R32_FLOAT;
					break;
				case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
					nativeDesc.Format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
					break;
				case DXGI_FORMAT_D24_UNORM_S8_UINT:
					nativeDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
					break;
				case DXGI_FORMAT_D16_UNORM:
					nativeDesc.Format = DXGI_FORMAT_R16_UNORM;
					break;
				default:
					nativeDesc.Format = resourceDesc.Format;
					break;
				}

				switch (resourceDesc.Dimension)
				{
				case D3D12_RESOURCE_DIMENSION_UNKNOWN:
					// ここに入ってきたらTextureCubeの可能性があるのかな???
					// わからんから今はとめておく
					assert(!"リソースのDimensionがおかしいです");
					break;
				case D3D12_RESOURCE_DIMENSION_BUFFER:
					nativeDesc.Format = DXGI_FORMAT_UNKNOWN;
					nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
					nativeDesc.Buffer.FirstElement = 0;
					// ByteAddressBufferを使用する場合はこちら
					if (raw)
					{
						nativeDesc.Buffer.NumElements = resourceDesc.Width / 4;
						nativeDesc.Buffer.StructureByteStride = 0;
						nativeDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
						nativeDesc.Format = DXGI_FORMAT_R32_TYPELESS;
					}
					else
					{
						nativeDesc.Buffer.NumElements = resourceDesc.Width / stride;
						nativeDesc.Buffer.StructureByteStride = stride;
						nativeDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
					}
					break;
				case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
						nativeDesc.Texture1DArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture1DArray.FirstArraySlice = 0;
						nativeDesc.Texture1DArray.MipLevels = 0;
						nativeDesc.Texture1DArray.MostDetailedMip = 0;
						nativeDesc.Texture1DArray.ResourceMinLODClamp = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
						nativeDesc.Texture1D.MipLevels = 0;
						nativeDesc.Texture1D.MostDetailedMip = 0;
						nativeDesc.Texture1D.ResourceMinLODClamp = 0.0f;
					}

					break;
				case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
					// マルチサンプリング
					if (resourceDesc.SampleDesc.Count != 1)
					{
						if (resourceDesc.DepthOrArraySize > 1)
						{
							nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY;
							nativeDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
							nativeDesc.Texture2DMSArray.FirstArraySlice = 0;
						}
						else
						{
							nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
							//nativeDesc.Texture2DMS.UnusedField_NothingToDefine;

						}
					}
					else
					{
						if (resourceDesc.DepthOrArraySize > 1)
						{
							nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
							nativeDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
							nativeDesc.Texture2DArray.FirstArraySlice = 0;
							nativeDesc.Texture2DArray.MipLevels = resourceDesc.MipLevels;
							nativeDesc.Texture2DArray.MostDetailedMip = resourceDesc.MipLevels;
							nativeDesc.Texture2DArray.ResourceMinLODClamp = 0;
						}
						else
						{
							nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
							nativeDesc.Texture2D.MipLevels = resourceDesc.MipLevels;
							nativeDesc.Texture2D.MostDetailedMip = resourceDesc.MipLevels - 1;
							nativeDesc.Texture2D.ResourceMinLODClamp = 0;

						}

					}

					break;
				case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
				{
					nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
					nativeDesc.Texture3D.MipLevels = resourceDesc.MipLevels;
					nativeDesc.Texture3D.MostDetailedMip = resourceDesc.MipLevels - 1;
					nativeDesc.Texture3D.ResourceMinLODClamp = 0;

				}
				break;
				default:
					assert(!"リソースのDimensionがおかしいです");
					break;
				}

			}
			m_device->CreateShaderResourceView(resource, &nativeDesc, handle);
		}

		void D3D12Device::CreateRenderTargetView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const
		{
			D3D12_RENDER_TARGET_VIEW_DESC nativeDesc = {};
			
			auto resourceDesc = resource->GetDesc();

			switch (resourceDesc.Dimension)
			{
			case D3D12_RESOURCE_DIMENSION_UNKNOWN:
				assert(!"");
				break;
			case D3D12_RESOURCE_DIMENSION_BUFFER:
				nativeDesc.Buffer.FirstElement = 0;
				nativeDesc.Buffer.NumElements = 0;
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
				nativeDesc.Texture1D.MipSlice = 0;
				nativeDesc.Texture1DArray.ArraySize = 0;
				nativeDesc.Texture1DArray.FirstArraySlice = 0;
				nativeDesc.Texture1DArray.MipSlice = 0;

				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
				if (resourceDesc.SampleDesc.Count != 1)
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
						nativeDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DMSArray.FirstArraySlice = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
						nativeDesc.Texture2DMS.UnusedField_NothingToDefine = 0;
					}
				}
				else
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
						nativeDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DArray.FirstArraySlice = 0;
						nativeDesc.Texture2DArray.MipSlice = 0;
						nativeDesc.Texture2DArray.PlaneSlice = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
						nativeDesc.Texture2D.MipSlice = 0;
						nativeDesc.Texture2D.PlaneSlice = 0;
					}

				}
				
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
				nativeDesc.Texture3D.FirstWSlice = 0;
				nativeDesc.Texture3D.MipSlice = 0;
				nativeDesc.Texture3D.WSize = 0;

				break;
			default:
				assert(!"");
				break;
			}

			m_device->CreateRenderTargetView(resource, &nativeDesc, handle);
		}

		void D3D12Device::CreateDepthStencilView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const
		{
			D3D12_DEPTH_STENCIL_VIEW_DESC nativeDesc = {};
			auto resourceDesc = resource->GetDesc();
			switch (resourceDesc.Dimension)
			{
			case D3D12_RESOURCE_DIMENSION_UNKNOWN:
				assert(!"");
				break;
			case D3D12_RESOURCE_DIMENSION_BUFFER:
				assert(!"バッファを使用してデプスステンシルビューは作成できません");
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
				nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
				nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1DARRAY;
				nativeDesc.Texture1D.MipSlice = 0;
				nativeDesc.Texture1DArray.ArraySize = 0;
				nativeDesc.Texture1DArray.FirstArraySlice = 0;
				nativeDesc.Texture1DArray.MipSlice = 0;

				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
				// マルチサンプリング
				if (resourceDesc.SampleDesc.Count != 1)
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY;
						nativeDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DMSArray.FirstArraySlice = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;

					}
				}
				else
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
						nativeDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DArray.FirstArraySlice = 0;
						nativeDesc.Texture2DArray.MipSlice = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
						nativeDesc.Texture2D.MipSlice = 0;
					}

				}

				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
				assert(!"");
				break;
			default:
				assert(!"");

				break;
			}

			m_device->CreateDepthStencilView(resource, &nativeDesc, handle);
			
		}

		void D3D12Device::CreateUnorderedAccessView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle, uint32_t stride, bool raw) const
		{
			auto resourceDesc = resource->GetDesc();

			D3D12_UNORDERED_ACCESS_VIEW_DESC nativeDesc = {};
			nativeDesc.Format = resourceDesc.Format;
			switch (resourceDesc.Dimension)
			{
			case D3D12_RESOURCE_DIMENSION_UNKNOWN:
				assert(!"");

				break;
			case D3D12_RESOURCE_DIMENSION_BUFFER:
				nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
				nativeDesc.Buffer.FirstElement = 0;
				nativeDesc.Buffer.CounterOffsetInBytes = 0;
				// ByteAddressBufferを使用する場合はこちら
				if (raw)
				{
					nativeDesc.Buffer.NumElements = resourceDesc.Width / 4;
					nativeDesc.Buffer.StructureByteStride = 0;
					nativeDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
					nativeDesc.Format = DXGI_FORMAT_R32_TYPELESS;
				}
				else
				{
					nativeDesc.Buffer.NumElements = resourceDesc.Width / stride;
					nativeDesc.Buffer.StructureByteStride = stride;
					nativeDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
				}
				//nativeDesc.Buffer.NumElements = 1;
				//nativeDesc.Buffer.StructureByteStride = resourceDesc.Width;
				//nativeDesc.Buffer.Flags
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
				if (resourceDesc.DepthOrArraySize > 1)
				{
					nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE1DARRAY;
					nativeDesc.Texture1DArray.ArraySize = 0;
					nativeDesc.Texture1DArray.FirstArraySlice = 0;
					nativeDesc.Texture1DArray.MipSlice = 0;
				}
				else
				{
					nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE1D;
					nativeDesc.Texture1D.MipSlice = 0;
				}
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
				if (resourceDesc.DepthOrArraySize > 1)
				{
					nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
					nativeDesc.Texture2DArray.ArraySize = 0;
					nativeDesc.Texture2DArray.FirstArraySlice = 0;
					nativeDesc.Texture2DArray.MipSlice = 0;
				}
				else
				{
					nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
					nativeDesc.Texture2D.MipSlice = 0;
					nativeDesc.Texture2D.PlaneSlice = 0;
				}
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
				nativeDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
				nativeDesc.Texture3D.MipSlice = 0;
				nativeDesc.Texture3D.FirstWSlice = 0;
				nativeDesc.Texture3D.WSize = 0;
				break;
			default:
				assert(!"");

				break;
			}
			m_device->CreateUnorderedAccessView(resource, nullptr, &nativeDesc, handle);

		}

		void D3D12Device::CreateConstantBufferView(ID3D12Resource1* resource, D3D12_CPU_DESCRIPTOR_HANDLE handle) const
		{
			D3D12_CONSTANT_BUFFER_VIEW_DESC nativeDesc = {};
			nativeDesc.BufferLocation = resource->GetGPUVirtualAddress();
			nativeDesc.SizeInBytes = (UINT)resource->GetDesc().Width;
			m_device->CreateConstantBufferView(&nativeDesc, handle);
		}

		ID3D12RootSignature* D3D12Device::CreateNativeRootSignature(ID3DBlob* blob) const
		{
			ID3D12RootSignature* rootSignature = nullptr;
			if (FAILED(m_device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&rootSignature))))
			{
				return nullptr;
			}

			return rootSignature;
		}

		ID3DBlob* D3D12Device::SerializeRootSignature(const D3D12_ROOT_SIGNATURE_DESC& desc) const
		{
			ID3DBlob* blob = nullptr;
			ID3DBlob* error = nullptr;

			if (FAILED(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &error))) 
			{
				auto er = ConvertBlobToString(error);
				MessageBox(nullptr, er.c_str(), "", MB_OK);
			}
			return  blob;
		}

	}
}
