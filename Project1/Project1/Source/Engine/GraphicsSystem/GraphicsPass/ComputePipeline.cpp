#include "ComputePipeline.h"
#include "..//Description/ComputePipelineDesc.h"
#include "..//D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "..//Shader/Shader.h"
#include "..//HardwareBuffer/RootSignature.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		ComputePipeline::ComputePipeline()
			: m_interface(nullptr)
			, m_rootSignature(nullptr)
			, m_computeShader(nullptr)
		{
		}

		ComputePipeline::~ComputePipeline()
		{
			delete m_rootSignature;
			delete m_computeShader;
			delete m_interface;
		}
		
		void ComputePipeline::SetRootSignature(RootSignature* rootSignature)
		{
			m_rootSignature = rootSignature;
		}

		void ComputePipeline::SetComputeShader(Shader* shader)
		{
			m_computeShader = shader;
		}
		
		void ComputePipeline::Create()
		{
			auto device = GetD3D12Device();
			ComputePipelineDesc desc = {};
			desc.computeShader = m_computeShader->GetInterface();
			desc.rootSignature = m_rootSignature->GetInterface();
			desc.nodeMask = 0;
			m_interface = device->CreateComputePipeline(desc);
		}

		IComputePipeline* ComputePipeline::GetInterface() const
		{
			return m_interface;
		}

		RootSignature* ComputePipeline::GetRootSignature() const
		{
			return m_rootSignature;
		}
	}

}
