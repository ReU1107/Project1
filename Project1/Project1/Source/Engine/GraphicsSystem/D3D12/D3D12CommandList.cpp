#include "D3D12CommandList.h"
#include <d3d12.h>
#include <cassert>
#include <vector>
#include "D3D12Resource.h"
#include "..//Description/Include.h"
#include "..//Enumerations/Include.h"
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

namespace Engine
{
	namespace GraphicsSystem
	{

		D3D12CommandList::D3D12CommandList()
			: m_nativeList(nullptr)
			, m_nativeAllocator(nullptr)
		{
		}

		D3D12CommandList::~D3D12CommandList()
		{
			m_nativeAllocator->Release();
			m_nativeList->Release();
		}

		void* D3D12CommandList::GetNativeCommandList() const
		{
			return m_nativeList;
		}

		void D3D12CommandList::ClearRenderTarget(IResourceView* renderTargetView, const Rect& rect, float color[4]) const
		{
			auto handle = ((D3D12ResourceView*)renderTargetView)->m_cpuHandle;
			D3D12_RECT nativeRect = {};
			nativeRect.left = (LONG)rect.left;
			nativeRect.right = (LONG)rect.right;
			nativeRect.top = (LONG)rect.top;
			nativeRect.bottom = (LONG)rect.bottom;
			m_nativeList->ClearRenderTargetView(handle, color, 1, &nativeRect);
		}

		void D3D12CommandList::ClearDepthStencil(IResourceView* depthStencilView, const Rect& rect, float depth, uint8_t stencil) const
		{
			auto handle = ((D3D12ResourceView*)depthStencilView)->m_cpuHandle;
			D3D12_RECT nativeRect = {};
			nativeRect.left = (LONG)rect.left;
			nativeRect.right = (LONG)rect.right;
			nativeRect.top = (LONG)rect.top;
			nativeRect.bottom = (LONG)rect.bottom;
			m_nativeList->ClearDepthStencilView(handle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, depth, stencil, 1, &nativeRect);
		}

		void D3D12CommandList::DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) const
		{
			m_nativeList->Dispatch(threadGroupX, threadGroupY, threadGroupZ);
		}

		void D3D12CommandList::BuildBottomLevelAccelerationStructure(IAccelerationStructure* as) const
		{
			D3D12BottomLevelAccelerationStructure* bottomLevelAS = nullptr;
			bottomLevelAS = (D3D12BottomLevelAccelerationStructure*)as;

			// バッファを作成するのに必要なサイズ取得
			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs = {};
			inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
			inputs.Flags = bottomLevelAS->m_flags;
			inputs.NumDescs = (UINT)bottomLevelAS->m_nativeDescs.size();
			inputs.pGeometryDescs = bottomLevelAS->m_nativeDescs.data();
			inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;

			// 
			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC structureDesc = {};
			structureDesc.Inputs = inputs;
			structureDesc.DestAccelerationStructureData = bottomLevelAS->m_result->GetGPUVirtualAddress();
			structureDesc.ScratchAccelerationStructureData = bottomLevelAS->m_scratch->GetGPUVirtualAddress();
			structureDesc.SourceAccelerationStructureData;

			m_nativeList->BuildRaytracingAccelerationStructure(&structureDesc, 0, nullptr);

			D3D12_RESOURCE_BARRIER uavBarrier = {};
			uavBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			uavBarrier.UAV.pResource = bottomLevelAS->m_result;
			m_nativeList->ResourceBarrier(1, &uavBarrier);
		}

		void D3D12CommandList::BuildTopLevelAccelerationStructure(IAccelerationStructure* as) const
		{
			D3D12TopLevelAccelerationStructure* topLevelAS = nullptr;
			topLevelAS = (D3D12TopLevelAccelerationStructure*)as;
			m_nativeList->BuildRaytracingAccelerationStructure(&topLevelAS->m_desc, 0, nullptr);

			D3D12_RESOURCE_BARRIER uavBarrier = {};
			uavBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			uavBarrier.UAV.pResource = topLevelAS->m_result;
			m_nativeList->ResourceBarrier(1, &uavBarrier);
		}

		void D3D12CommandList::DispatchRaytracing(const RaytracingDispatchDesc& desc) const
		{
			D3D12_DISPATCH_RAYS_DESC rayDesc = {};

			rayDesc.Width = desc.width;
			rayDesc.Height = desc.height;
			rayDesc.Depth = desc.depth;

			ID3D12Resource1* rayGenerate = (ID3D12Resource1*)desc.rayGenerate->GetNativeResource();

			rayDesc.RayGenerationShaderRecord.StartAddress = rayGenerate->GetGPUVirtualAddress();
			rayDesc.RayGenerationShaderRecord.SizeInBytes = desc.rayGenerateSize;

			ID3D12Resource1* miss = (ID3D12Resource1*)desc.missTable->GetNativeResource();
			rayDesc.MissShaderTable.StartAddress = miss->GetGPUVirtualAddress();
			rayDesc.MissShaderTable.SizeInBytes = desc.missSize;
			rayDesc.MissShaderTable.StrideInBytes = desc.missStride;

			ID3D12Resource1* hitGroup = (ID3D12Resource1*)desc.hitGroupTable->GetNativeResource();

			rayDesc.HitGroupTable.StartAddress = hitGroup->GetGPUVirtualAddress();
			rayDesc.HitGroupTable.SizeInBytes = desc.hitGroupSize;
			rayDesc.HitGroupTable.StrideInBytes = desc.hitGroupStride;
			// 今は無視
			rayDesc.CallableShaderTable;

			m_nativeList->DispatchRays(&rayDesc);
		}

		void D3D12CommandList::ResourceBarrierTransition(IResource* resources[], uint32_t resourceCount, ResourceStates before, ResourceStates after, uint32_t subResourceCount) const
		{
			D3D12_RESOURCE_BARRIER barrier[10] = {};
			for (uint32_t i = 0; i < resourceCount; ++i)
			{
				ID3D12Resource1* resource = (ID3D12Resource1*)resources[i]->GetNativeResource();
				barrier[i].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				barrier[i].Transition.pResource = resource;
				barrier[i].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				barrier[i].Transition.StateBefore = D3D12ResourceStates(before);
				barrier[i].Transition.StateAfter = D3D12ResourceStates(after);

			}

			m_nativeList->ResourceBarrier(resourceCount, barrier);
		}

		void D3D12CommandList::SetDescriptorHeaps(IDescriptorHeap* descriptorHeaps[], uint32_t heapCount) const
		{
			ID3D12DescriptorHeap* heaps[4];
			for (uint32_t i = 0; i < heapCount; ++i)
			{
				heaps[i] = (ID3D12DescriptorHeap*)descriptorHeaps[i]->GetNativeHeap();
			}
			m_nativeList->SetDescriptorHeaps(heapCount, heaps);
		}

		void D3D12CommandList::SetComputeDescriptorTable(IResourceView* view, uint32_t parameterIndex) const
		{
			auto handle = ((D3D12ResourceView*)view)->m_gpuHandle;
			m_nativeList->SetComputeRootDescriptorTable(parameterIndex, handle);
		}

		void D3D12CommandList::SetComputeDescriptorTable(IDescriptorHeap* descriptorHeap, uint32_t parameterIndex) const
		{
			ID3D12DescriptorHeap* heap = (ID3D12DescriptorHeap*)descriptorHeap->GetNativeHeap();
			auto handle = heap->GetGPUDescriptorHandleForHeapStart();
			m_nativeList->SetComputeRootDescriptorTable(parameterIndex, handle);
		}

		void D3D12CommandList::SetComputeShaderResource(IResource* resource, uint32_t parameterIndex) const
		{
			auto nativeResource = (ID3D12Resource1*)resource->GetNativeResource();
			m_nativeList->SetComputeRootShaderResourceView(parameterIndex, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::SetComputeConstantBuffer(IResource* resource, uint32_t parameterIndex) const
		{
			auto nativeResource = (ID3D12Resource1*)resource->GetNativeResource();
			m_nativeList->SetComputeRootConstantBufferView(parameterIndex, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::SetComputeUnorderedAccess(IResource* resource, uint32_t parameterIndex) const
		{
			auto nativeResource = (ID3D12Resource1*)resource->GetNativeResource();
			m_nativeList->SetComputeRootUnorderedAccessView(parameterIndex, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::UnorderedAccessBarrier(IResource* resources[], uint32_t resourceCount) const
		{
			D3D12_RESOURCE_BARRIER barrier[10] = {};
			for (uint32_t i = 0; i < resourceCount; ++i)
			{
				ID3D12Resource1* resource = (ID3D12Resource1*)resources[i]->GetNativeResource();
				barrier[i].Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
				barrier[i].UAV.pResource = resource;
			}

			m_nativeList->ResourceBarrier(resourceCount, barrier);
		}

		void D3D12CommandList::SetComputeRootSignature(IRootSignature* rootSignature) const
		{
			ID3D12RootSignature* root = (ID3D12RootSignature*)rootSignature->GetNativeSignature();
			m_nativeList->SetComputeRootSignature(root);
		}

		void D3D12CommandList::SetGraphicsRootSignature(IRootSignature* rootSignature) const
		{
			ID3D12RootSignature* root = (ID3D12RootSignature*)rootSignature->GetNativeSignature();
			m_nativeList->SetGraphicsRootSignature(root);
		}

		void D3D12CommandList::SetGraphicsRootDescriptorTable(IResourceView* view, uint32_t index) const
		{
			D3D12ResourceView* nativeView = (D3D12ResourceView*)view;
			m_nativeList->SetGraphicsRootDescriptorTable(index, nativeView->m_gpuHandle);
		}

		void D3D12CommandList::SetGraphicsShaderResource(IResource* resource, uint32_t index) const
		{
			ID3D12Resource* nativeResource = (ID3D12Resource*)resource->GetNativeResource();
			m_nativeList->SetGraphicsRootShaderResourceView(index, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::SetGraphicsConstantBuffer(IResource* resource, uint32_t index) const
		{
			ID3D12Resource* nativeResource = (ID3D12Resource*)resource->GetNativeResource();
			m_nativeList->SetGraphicsRootConstantBufferView(index, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::SetGraphicsUnorderedAccess(IResource* resource, uint32_t index) const
		{
			ID3D12Resource* nativeResource = (ID3D12Resource*)resource->GetNativeResource();
			m_nativeList->SetGraphicsRootUnorderedAccessView(index, nativeResource->GetGPUVirtualAddress());
		}

		void D3D12CommandList::SetRaytracingPipeline(IRaytracingPipeline* pipeline) const
		{
			ID3D12StateObject* pipelineState = (ID3D12StateObject*)pipeline->GetNativePipeline();
			m_nativeList->SetPipelineState1(pipelineState);
		}

		void D3D12CommandList::SetRasterizerPipeline(IRasterizerPipeline* pipeline) const
		{
			ID3D12PipelineState* pipelineState = (ID3D12PipelineState*)pipeline->GetNativePipeline();
			m_nativeList->SetPipelineState(pipelineState);
		}

		void D3D12CommandList::SetComputePipeline(IComputePipeline* pipeline) const
		{
			ID3D12PipelineState* pipelineState = (ID3D12PipelineState*)pipeline->GetNativePipeline();
			m_nativeList->SetPipelineState(pipelineState);
		}

		void D3D12CommandList::SetPrimitiveTopology(PrimitiveTopology topology) const
		{
			m_nativeList->IASetPrimitiveTopology(D3D12PrimitiveTopology(topology));
		}

		void D3D12CommandList::SetVertexBuffers(IResource* resources[], uint64_t strides[], uint64_t sizes[], uint32_t start, uint32_t count) const
		{
			D3D12_VERTEX_BUFFER_VIEW views[20] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				auto& view = views[i];
				auto resource = resources[i];
				if (resource)
				{
					auto buffer = (ID3D12Resource1*)resource->GetNativeResource();
					view.BufferLocation = buffer->GetGPUVirtualAddress();
				}
				view.StrideInBytes = strides[i];
				view.SizeInBytes = sizes[i];
			}

			m_nativeList->IASetVertexBuffers(start, count, views);
		}

		void D3D12CommandList::SetIndexBuffer(IResource* resource, uint64_t size, IndexFormat format) const
		{
			D3D12_INDEX_BUFFER_VIEW view = {};
			ID3D12Resource1* indexBuffer = (ID3D12Resource1*)resource->GetNativeResource();
			view.BufferLocation = indexBuffer->GetGPUVirtualAddress();
			view.Format = DXGIIndexFormat(format);
			view.SizeInBytes = size;
			m_nativeList->IASetIndexBuffer(&view);
		}

		void D3D12CommandList::SetScissorRects(const Rect rects[], uint32_t count) const
		{
			D3D12_RECT nativeRects[10];
			for (uint32_t i = 0; i < count; ++i)
			{
				auto& source = rects[i];
				auto& destination = nativeRects[i];
				destination.left = (LONG)source.left;
				destination.right = (LONG)source.right;
				destination.top = (LONG)source.top;
				destination.bottom = (LONG)source.bottom;
			}
			m_nativeList->RSSetScissorRects(count, nativeRects);
		}

		void D3D12CommandList::SetViewports(const Viewport viewports[], uint32_t count) const
		{
			D3D12_VIEWPORT nativeViewports[10];
			for (uint32_t i = 0; i < count; ++i)
			{
				auto& source = viewports[i];
				auto& destination = nativeViewports[i];
				destination.TopLeftX = source.x;
				destination.TopLeftY = source.y;
				destination.Width = source.width;
				destination.Height = source.height;
				destination.MinDepth = source.minDepth;
				destination.MaxDepth = source.maxDepth;
			}

			m_nativeList->RSSetViewports(count, nativeViewports);
		}

		void D3D12CommandList::SetRenderTargets(IResourceView* renderTarget[], uint32_t count, IResourceView* depthStencil) const
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handles[8] = {};
			D3D12_CPU_DESCRIPTOR_HANDLE* depthStencilHandle = nullptr;
			for (uint32_t i = 0; i < count; ++i)
			{
				handles[i] = ((D3D12ResourceView*)renderTarget[i])->m_cpuHandle;
			}
			if (depthStencil)
			{
				depthStencilHandle = &((D3D12ResourceView*)depthStencil)->m_cpuHandle;
			}

			m_nativeList->OMSetRenderTargets(count, handles, false, depthStencilHandle);
		}

		void D3D12CommandList::CopyResource(IResource* source, IResource* destination) const
		{
			ID3D12Resource1* dst = (ID3D12Resource1*)destination->GetNativeResource();
			ID3D12Resource1* src = (ID3D12Resource1*)source->GetNativeResource();
			m_nativeList->CopyResource(dst, src);
		}

		void D3D12CommandList::CopyBuffer(IResource* source, IResource* destination, uint64_t byteSize, uint32_t sourceOffset, uint32_t destinationOffset) const
		{
			ID3D12Resource1* dst = (ID3D12Resource1*)destination->GetNativeResource();
			ID3D12Resource1* src = (ID3D12Resource1*)source->GetNativeResource();
			m_nativeList->CopyBufferRegion(dst, sourceOffset, src, destinationOffset, byteSize);
		}

		void D3D12CommandList::DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount, uint32_t startIndex, uint32_t startVertex, uint32_t startInstance) const
		{
			m_nativeList->DrawIndexedInstanced(useIndexCount, instanceCount, startIndex, startVertex, startInstance);
		}

		void D3D12CommandList::Close() const
		{
			auto hr = m_nativeList->Close();
		}

		void D3D12CommandList::Reset() const
		{
			auto hr = m_nativeAllocator->Reset();
			if (FAILED(hr))
			{
				assert(!"アロケーターのリセットに失敗しました");
			}
			hr = m_nativeList->Reset(m_nativeAllocator, nullptr);
			if (FAILED(hr))
			{
				assert(!"リストのリセットに失敗しました");
			}
		}

	}

}