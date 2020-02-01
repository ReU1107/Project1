#include "ComputeCommandList.h"
#include "..//D3D12/D3D12Device.h"
#include "..//D3D12.h"
#include "..//Description/CommandListDesc.h"
#include "..//Enumerations/CommandListType.h"
#include "../../Utility/Utility.h"
#include "..//..//Math/Rect.h"
#include <cassert>

namespace Engine
{
	namespace GraphicsSystem
	{
		ComputeCommandList::ComputeCommandList()
			: base()
		{
		}

		ComputeCommandList::~ComputeCommandList()
		{
		}

		ComputeCommandList::ComputeCommandListPtr ComputeCommandList::Create(const std::string& name)
		{
			auto device = GetD3D12Device();

			CommandListDesc desc = {};
			desc.type = CommandListType::Compute;

			auto list = std::make_shared<ComputeCommandList>();
			list->m_interface = device->CreateCommandList(desc);
			list->SetName(name);

			Register(name, list);

			return list;
		}

		void ComputeCommandList::SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const
		{
			base::SetDescriptorHeaps(descriptors, count);
		}

		void ComputeCommandList::DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const
		{
			base::DispatchRaytracing(width, height, depth, rayGenerate, hitGroup, miss, callable);
		}

		void ComputeCommandList::BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const
		{
			base::BuildBottomLevelAS(bottomLevelAS);
		}

		void ComputeCommandList::BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const
		{
			base::BuildTopLevelAS(topLevelAS);
		}

		void ComputeCommandList::SetRaytracingPipeline(RaytracingPipeline* pipeline) const
		{
			base::SetRaytracingPipeline(pipeline);
		}

		void ComputeCommandList::SetComputePipeline(ComputePipeline* pipeline) const
		{
			base::SetComputePipeline(pipeline);
		}

		void ComputeCommandList::SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const
		{
			base::SetComputeConstantBuffer(constantBuffer, registerIndex);
		}

		void ComputeCommandList::SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const
		{
			base::SetComputeShaderResource(texture, registerIndex);
		}

		void ComputeCommandList::SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const
		{
			base::SetComputeUnorderedAccess(texture, registerIndex);
		}

		void ComputeCommandList::SetComputeRootSignature(RootSignature* rootSignature) const
		{
			base::SetComputeRootSignature(rootSignature);
		}

		void ComputeCommandList::SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const
		{
			base::SetComputeDescriptorTable(headView, registerIndex);
		}

		void ComputeCommandList::SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const
		{
			base::SetComputeDescriptorTable(descriptor, registerIndex);
		}

		void ComputeCommandList::DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const
		{
			base::DispatchCompute(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
		}

		void ComputeCommandList::UnorderedAccessBarrier(Resource* resources[], uint32_t count) const
		{
			base::UnorderedAccessBarrier(resources, count);
		}

		void ComputeCommandList::ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const
		{
			base::ResourceBarrier(resources, count, after);
		}

		void ComputeCommandList::ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const
		{
			base::ResourceBarrier(buffers, count, after);
		}

		void ComputeCommandList::CopyResource(Resource* source, Resource* destination) const
		{
			base::CopyResource(source, destination);
		}

		void ComputeCommandList::CopyBuffer(Buffer* buffer) const
		{
			base::CopyBuffer(buffer);
		}
		
	}
}