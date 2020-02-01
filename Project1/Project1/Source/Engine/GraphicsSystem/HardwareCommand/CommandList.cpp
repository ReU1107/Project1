#include "CommandList.h"
#include "..//Interface/ICommandList.h"
#include "..//HardwareBuffer/Include.h"
#include "..//Texture/Include.h"
#include "..//GraphicsPass/Include.h"
#include "..//Shader/Include.h"
#include "..//Description/RaytracingDispatchDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		CommandList::CommandList()
			: base("コマンドリスト")
			, m_interface(nullptr)
		{
		}

		CommandList::~CommandList()
		{
			delete m_interface;
		}

		ICommandList* CommandList::GetInterface() const
		{
			return m_interface;
		}

		void CommandList::ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color) const
		{
			m_interface->ClearRenderTarget(view->GetInterface(), rect, (float*)& color);
		}

		void CommandList::ClearDepthStencil(ResourceView* view, const Rect& rect, float depth, uint8_t stencil) const
		{
			m_interface->ClearDepthStencil(view->GetInterface(), rect, depth, stencil);
		}

		void CommandList::SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start) const
		{
			IResource* resources[11] = {};
			uint64_t strides[11] = {};
			uint64_t sizes[11] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				auto vertexBuffer = vertexBuffers[i];
				if (vertexBuffer)
				{
					resources[i] = vertexBuffers[i]->GetInterface();
					strides[i] = vertexBuffers[i]->GetStride();
					sizes[i] = vertexBuffers[i]->GetSize();
				}
				else
				{
					i = i;
				}
			}
			m_interface->SetVertexBuffers(resources, strides, sizes, start, count);
		}

		void CommandList::SetIndexBuffer(IndexBuffer* indexBuffer) const
		{
			IResource* resource = indexBuffer->GetInterface();
			uint64_t size = indexBuffer->GetSize();
			IndexFormat format = indexBuffer->GetFormat();
			m_interface->SetIndexBuffer(resource, size, format);
		}

		void CommandList::SetTopology(PrimitiveTopology topology) const
		{
			m_interface->SetPrimitiveTopology(topology);
		}

		void CommandList::SetViewports(const Viewport viewports[], uint32_t count) const
		{
			m_interface->SetViewports(viewports, count);
		}

		void CommandList::SetScissorRects(const Rect rects[], uint32_t count) const
		{
			m_interface->SetScissorRects(rects, count);
		}

		void CommandList::SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const
		{
			IResourceView* targets[8] = {};
			IResourceView* depth = nullptr;
			for (uint32_t i = 0; i < count; ++i)
			{
				targets[i] = renderTargets[i]->GetRenderTargetView()->GetInterface();
			}
			if (depthStencil)
			{
				depth = depthStencil->GetDepthStencilView()->GetInterface();
			}
			m_interface->SetRenderTargets(targets, count, depth);
		}

		void CommandList::SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const
		{
			IDescriptorHeap* heaps[4] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				heaps[i] = descriptors[i]->GetInterface();
			}
			m_interface->SetDescriptorHeaps(heaps, count);
		}

		void CommandList::SetRaytracingPipeline(RaytracingPipeline* pipeline) const
		{
			IRaytracingPipeline* pipe = pipeline->GetInterface();
			m_interface->SetRaytracingPipeline(pipe);
		}

		void CommandList::SetRasterizerPipeline(RasterizerPipeline* pipeline) const
		{
			IRasterizerPipeline* pipe = pipeline->GetInterface();
			m_interface->SetRasterizerPipeline(pipe);
		}

		void CommandList::SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const
		{
			IResource* resource = constantBuffer->GetInterface();
			m_interface->SetGraphicsConstantBuffer(resource, registerIndex);
		}

		void CommandList::SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const
		{
			IResource* resource = texture->GetResource()->GetInterface();
			m_interface->SetGraphicsShaderResource(resource, registerIndex);
		}

		void CommandList::SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const
		{
			IResource* resource = texture->GetResource()->GetInterface();
			m_interface->SetGraphicsUnorderedAccess(resource, registerIndex);
		}

		void CommandList::SetGraphicsRootSignature(RootSignature* rootSignature) const
		{
			IRootSignature* signature = rootSignature->GetInterface();
			m_interface->SetGraphicsRootSignature(signature);
		}

		void CommandList::SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const
		{
			IResourceView* view = headView->GetInterface();
			m_interface->SetGraphicsRootDescriptorTable(view, registerIndex);
		}

		void CommandList::SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const
		{
			IResource* resource = constantBuffer->GetInterface();
			m_interface->SetComputeConstantBuffer(resource, registerIndex);
		}

		void CommandList::SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const
		{
			IResource* resource = texture->GetResource()->GetInterface();
			m_interface->SetComputeShaderResource(resource, registerIndex);
		}

		void CommandList::SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const
		{
			IResource* resource = texture->GetResource()->GetInterface();
			m_interface->SetComputeUnorderedAccess(resource, registerIndex);
		}

		void CommandList::SetComputeRootSignature(RootSignature* rootSignature) const
		{
			IRootSignature* signature = rootSignature->GetInterface();
			m_interface->SetComputeRootSignature(signature);
		}

		void CommandList::SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const
		{
			IResourceView* view = headView->GetInterface();
			m_interface->SetComputeDescriptorTable(view, registerIndex);
		}

		void CommandList::SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const
		{
			IDescriptorHeap* heap = descriptor->GetInterface();
			m_interface->SetComputeDescriptorTable(heap, registerIndex);
		}

		void CommandList::DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const
		{
			m_interface->DispatchCompute(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
		}

		void CommandList::UnorderedAccessBarrier(Resource* resources[], uint32_t count) const
		{
			IResource* nativeResources[10] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				nativeResources[i] = resources[i]->GetInterface();
			}

			m_interface->UnorderedAccessBarrier(nativeResources, count);
		}

		void CommandList::UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const
		{
			IResource* nativeResources[10] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				nativeResources[i] = buffers[i]->GetInterface();
			}

			m_interface->UnorderedAccessBarrier(nativeResources, count);
		}

		void CommandList::ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const
		{
			IResource* res[5] = {};
			ResourceStates before = resources[0]->GetStates();
			for (uint32_t i = 0; i < count; ++i)
			{
				res[i] = resources[i]->GetInterface();
				resources[i]->SetStates(after);
			}
			m_interface->ResourceBarrierTransition(res, count, before, after);
		}

		void CommandList::ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const
		{
			IResource* res[10] = {};
			ResourceStates before = buffers[0]->GetStates();
			for (uint32_t i = 0; i < count; ++i)
			{
				res[i] = buffers[i]->GetInterface();
				buffers[i]->SetStates(after);
			}
			m_interface->ResourceBarrierTransition(res, count, before, after);
		}

		void CommandList::DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const
		{
			RaytracingDispatchDesc desc = {};
			desc.width = width;
			desc.height = height;
			desc.depth = depth;

			desc.rayGenerate = rayGenerate->GetInterface();
			desc.rayGenerateSize = rayGenerate->GetSize();

			desc.hitGroupTable = hitGroup->GetInterface();
			desc.hitGroupStride = hitGroup->GetStride();
			desc.hitGroupSize = hitGroup->GetSize();

			desc.missTable = miss->GetInterface();
			desc.missStride = miss->GetStride();
			desc.missSize = miss->GetSize();

			if (callable)
			{

			}

			m_interface->DispatchRaytracing(desc);
		}

		void CommandList::BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const
		{
			if (bottomLevelAS->IsDirty())
			{
				IAccelerationStructure* as = bottomLevelAS->GetInterface();
				m_interface->BuildBottomLevelAccelerationStructure(as);
				bottomLevelAS->Dirty(false);
			}
		}

		void CommandList::BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const
		{
			IAccelerationStructure* as = topLevelAS->GetInterface();
			m_interface->BuildTopLevelAccelerationStructure(as);
		}

		void CommandList::CopyResource(Resource* source, Resource* destination) const
		{
			IResource* src = source->GetInterface();
			IResource* dst = destination->GetInterface();
			m_interface->CopyResource(src, dst);
		}

		void CommandList::CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset, uint32_t dstOffset) const
		{
			auto dst = buffer->GetInterface();
			auto src = buffer->GetCopyable()->GetInterface();
			m_interface->CopyBuffer(src, dst, size, srcOffset, dstOffset);
		}

		void CommandList::CopyBuffer(Buffer* buffer) const
		{
			auto dst = buffer->GetInterface();
			auto src = buffer->GetCopyable()->GetInterface();
			m_interface->CopyResource(src, dst);
		}

		void CommandList::SetComputePipeline(ComputePipeline* pipeline) const
		{
			m_interface->SetComputePipeline(pipeline->GetInterface());
		}

		void CommandList::DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount, uint32_t startIndex, uint32_t startVertex, uint32_t startInstance) const
		{
			m_interface->DrawIndexedInstance(useIndexCount, instanceCount, startIndex, startVertex, startInstance);
		}

		void CommandList::Close() const
		{
			m_interface->Close();
		}

		void CommandList::Reset() const
		{
			m_interface->Reset();
		}

	}
}