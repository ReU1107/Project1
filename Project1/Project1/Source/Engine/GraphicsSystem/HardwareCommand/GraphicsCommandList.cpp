#include "GraphicsCommandList.h"
#include "..//D3D12/D3D12Device.h"
#include "..//D3D12.h"
#include "..//Description/CommandListDesc.h"
#include "..//Enumerations/CommandListType.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem
	{
		GraphicsCommandList::GraphicsCommandList()
			: base()
		{
		}

		GraphicsCommandList::~GraphicsCommandList()
		{
		}

		GraphicsCommandList::GraphicsCommandListPtr GraphicsCommandList::Create(const std::string& name)
		{
			auto device = GetD3D12Device();

			CommandListDesc desc = {};
			desc.type = CommandListType::General;

			auto list = std::make_shared<GraphicsCommandList>();
			list->m_interface = device->CreateCommandList(desc);
			list->SetName(name);

			Register(name, list);
			return list;
		}

		void GraphicsCommandList::ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color) const
		{
			base::ClearRenderTarget(view, rect, color);
		}

		void GraphicsCommandList::ClearDepthStencil(ResourceView* view, const Rect& rect, float depth, uint8_t stencil) const
		{
			base::ClearDepthStencil(view, rect, depth, stencil);
		}

		void GraphicsCommandList::SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start) const
		{
			base::SetVertexBuffers(vertexBuffers, count, start);
		}

		void GraphicsCommandList::SetIndexBuffer(IndexBuffer* indexBuffer) const
		{
			base::SetIndexBuffer(indexBuffer);
		}

		void GraphicsCommandList::SetTopology(PrimitiveTopology topology) const
		{
			base::SetTopology(topology);
		}

		void GraphicsCommandList::SetViewports(const Viewport viewports[], uint32_t count) const
		{
			base::SetViewports(viewports, count);
		}

		void GraphicsCommandList::SetScissorRects(const Rect rects[], uint32_t count) const
		{
			base::SetScissorRects(rects, count);
		}

		void GraphicsCommandList::SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const
		{
			base::SetRenderTargets(renderTargets, count, depthStencil);
		}

		void GraphicsCommandList::SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const
		{
			base::SetDescriptorHeaps(descriptors, count);
		}

		void GraphicsCommandList::SetRasterizerPipeline(RasterizerPipeline* pipeline) const
		{
			base::SetRasterizerPipeline(pipeline);
		}

		void GraphicsCommandList::SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const
		{
			base::SetGraphicsConstantBuffer(constantBuffer, registerIndex);
		}

		void GraphicsCommandList::SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const
		{
			base::SetGraphicsShaderResource(texture, registerIndex);
		}

		void GraphicsCommandList::SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const
		{
			base::SetGraphicsUnorderedAccess(texture, registerIndex);
		}

		void GraphicsCommandList::SetGraphicsRootSignature(RootSignature* rootSignature) const
		{
			base::SetGraphicsRootSignature(rootSignature);
		}

		void GraphicsCommandList::SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const
		{
			base::SetGraphicsDescriptorTable(headView, registerIndex);
		}

		void GraphicsCommandList::ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const
		{
			base::ResourceBarrier(resources, count, after);
		}

		void GraphicsCommandList::DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount, uint32_t startIndex, uint32_t startVertex, uint32_t startInstance) const
		{
			base::DrawIndexedInstance(useIndexCount, instanceCount, startIndex, startVertex, startInstance);
		}

		void GraphicsCommandList::DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const
		{
			base::DispatchRaytracing(width, height, depth, rayGenerate, hitGroup, miss, callable);
		}

		void GraphicsCommandList::BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const
		{
			base::BuildBottomLevelAS(bottomLevelAS);
		}

		void GraphicsCommandList::BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const
		{
			base::BuildTopLevelAS(topLevelAS);
		}

		void GraphicsCommandList::SetRaytracingPipeline(RaytracingPipeline* pipeline) const
		{
			base::SetRaytracingPipeline(pipeline);
		}

		void GraphicsCommandList::SetComputePipeline(ComputePipeline* pipeline) const
		{
			base::SetComputePipeline(pipeline);
		}

		void GraphicsCommandList::SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const
		{
			base::SetComputeConstantBuffer(constantBuffer, registerIndex);
		}

		void GraphicsCommandList::SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const
		{
			base::SetComputeShaderResource(texture, registerIndex);
		}

		void GraphicsCommandList::SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const
		{
			base::SetComputeUnorderedAccess(texture, registerIndex);
		}

		void GraphicsCommandList::SetComputeRootSignature(RootSignature* rootSignature) const
		{
			base::SetComputeRootSignature(rootSignature);
		}

		void GraphicsCommandList::SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const
		{
			base::SetComputeDescriptorTable(headView, registerIndex);
		}

		void GraphicsCommandList::SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const
		{
			base::SetComputeDescriptorTable(descriptor, registerIndex);
		}

		void GraphicsCommandList::DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const
		{
			base::DispatchCompute(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
		}

		void GraphicsCommandList::UnorderedAccessBarrier(Resource* resources[], uint32_t count) const
		{
			base::UnorderedAccessBarrier(resources, count);
		}

		void GraphicsCommandList::UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const
		{
			base::UnorderedAccessBarrier(buffers, count);
		}

		void GraphicsCommandList::CopyResource(Resource* source, Resource* destination) const
		{
			base::CopyResource(source, destination);
		}

		void GraphicsCommandList::ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const
		{
			base::ResourceBarrier(buffers, count, after);
		}

		void GraphicsCommandList::CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset, uint32_t dstOffset) const
		{
			base::CopyBuffer(buffer, size, srcOffset, dstOffset);
		}

		void GraphicsCommandList::CopyBuffer(Buffer* buffer) const
		{
			base::CopyBuffer(buffer);
		}
	}
}