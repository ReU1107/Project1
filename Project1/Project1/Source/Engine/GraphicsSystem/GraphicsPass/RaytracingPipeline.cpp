#include "RaytracingPipeline.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Description/Include.h"
#include "../Interface/IRaytracingPipeline.h"
#include "../Enumerations/Include.h"
#include "..//HardwareBuffer/RootSignature.h"
#include "../Shader/ShaderLibrary.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		RaytracingPipeline::RaytracingPipeline()
			: m_interface(nullptr)
			, m_parameters()
		{
		}

		RaytracingPipeline::~RaytracingPipeline()
		{
			delete m_interface;
		}

		void RaytracingPipeline::AddParameterDesc(const RaytracingPipelineParameterDesc& desc)
		{
			m_parameters.push_back(desc);
		}

		void RaytracingPipeline::SetRaytraceMaxCount(uint32_t maxCount)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.pipelineConfig.raytraceMaxCount = maxCount;
			desc.parameterType = RaytracingPipelineParameterType::PipelineConfig;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::SetShaderConfig(uint32_t attributeSize, uint32_t payloadSize)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.shaderConfig.attributeSize = attributeSize;
			desc.shaderConfig.payloadSize = payloadSize;
			desc.parameterType = RaytracingPipelineParameterType::ShaderConfig;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::AddAssociation(const wchar_t** shaderNames, uint32_t shaderCount, int32_t index)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.association.shaderNames = shaderNames;
			desc.association.shaderCount = shaderCount;
			desc.association.index = (index < 0) ? (m_parameters.size() - 1) : index;
			desc.parameterType = RaytracingPipelineParameterType::Association;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::AddShaderLibrary(ShaderLibrary* shaderLibrary)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.shaderLibrary.shaderCount = shaderLibrary->GetShaderFunctionCount();
			desc.shaderLibrary.shader = shaderLibrary->GetInterface();
			desc.shaderLibrary.shaderNames = shaderLibrary->GetFunctionNames();
			desc.parameterType = RaytracingPipelineParameterType::ShaderLibrary;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::AddLocalRootSignature(RootSignature* localRootSignature, const wchar_t** usedShaders, uint32_t shaderCount)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.signature.rootSignature = localRootSignature->GetInterface();
			desc.signature.type = localRootSignature->GetType();
			desc.parameterType = RaytracingPipelineParameterType::Signature;
			AddParameterDesc(desc);

			AddAssociation(usedShaders, shaderCount);
		}

		void RaytracingPipeline::AddGlobalRootSignature(RootSignature* globalRootSignature)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.signature.rootSignature = globalRootSignature->GetInterface();
			desc.signature.type = globalRootSignature->GetType();
			desc.parameterType = RaytracingPipelineParameterType::Signature;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::AddHitGroup(const wchar_t* groupName, const wchar_t* hitShaderName, const wchar_t* intersectShaderName, const wchar_t* anyHitShaderName)
		{
			RaytracingPipelineParameterDesc desc = {};
			desc.hitGroup.name = groupName;
			desc.hitGroup.type = (intersectShaderName) ? BottomLevelType::Procedural : BottomLevelType::Traiangles;
			desc.hitGroup.hitShader = hitShaderName;
			desc.hitGroup.intersectShader = intersectShaderName;
			desc.hitGroup.anyHitShader = anyHitShaderName;
			desc.parameterType = RaytracingPipelineParameterType::HitGroup;
			AddParameterDesc(desc);
		}

		void RaytracingPipeline::Create()
		{
			RaytracingPipelineDesc desc = {};
			desc.parameters = m_parameters.data();
			desc.parameterCount = (uint32_t)m_parameters.size();
			m_interface = GetD3D12Device()->CreateRaytracingPipeline(desc);
		}

		void* RaytracingPipeline::GetShaderIdentifier(const wchar_t* exportName) const
		{
			return m_interface->GetShaderIdentifier(exportName);
		}

		IRaytracingPipeline* RaytracingPipeline::GetInterface() const
		{
			return m_interface;
		}

		void RaytracingPipeline::SetName(const std::wstring& name)
		{
			ID3D12Resource1* resource = (ID3D12Resource1*)m_interface->GetNativePipeline();
			resource->SetName(name.c_str());
		}
	}
}