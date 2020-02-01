#include "RasterizerPipeline.h"
#include "..//D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "..//../Utility/EnumOperator.h"
#include "..//Description/Include.h"
#include "..//Enumerations/Include.h"
#include "..//Shader/Shader.h"
#include "..//HardwareBuffer/RootSignature.h"

namespace Engine
{
	namespace GraphicsSystem
	{

		RasterizerPipeline::RasterizerPipeline()
			: m_interface(nullptr)
			, m_renderTargets()
			, m_vertexShader(nullptr)
			, m_pixelShader(nullptr)
			, m_domainShader(nullptr)
			, m_hullShader(nullptr)
			, m_geometryShader(nullptr)
			, m_rootSignature(nullptr)
			, m_rasterizerState()
			, m_blendState()
			, m_inputLayout()
			, m_depthStencilState()
			, m_renderTargetCount(1)
			, m_renderTargetFormats()
			, m_sampleCount(1)
			, m_sampleQuality(0)
			, m_sampleMask(UINT32_MAX)
			, m_nodeMask(0)
			, m_topology(PrimitiveTopology::TriangleList)
			, m_depthStencilFormat()
		{
		}

		RasterizerPipeline::~RasterizerPipeline()
		{

		}
		void RasterizerPipeline::SetVertexShader(Shader* shader)
		{
			m_vertexShader = shader;
		}

		void RasterizerPipeline::SetPixelShader(Shader* shader)
		{
			m_pixelShader = shader;
		}

		void RasterizerPipeline::SetRootSignature(RootSignature* rootSignature)
		{
			m_rootSignature = rootSignature;
		}

		void RasterizerPipeline::SetInputLayout(const InputLayoutDesc& inputLayout)
		{
			m_inputLayout = inputLayout;
		}

		void RasterizerPipeline::SetBlendState(const BlendDesc& blendDesc)
		{
			m_blendState = blendDesc;
		}

		void RasterizerPipeline::SetRasterizerState(const RasterizerDesc& rasterizerDesc)
		{
			m_rasterizerState = rasterizerDesc;
		}

		void RasterizerPipeline::SetDepthStencilState(const DepthStencilDesc& depthStencilDesc)
		{
			m_depthStencilState = depthStencilDesc;
		}

		void RasterizerPipeline::SetSampleDesc(uint32_t sampleCount, uint32_t sampleQuality)
		{
			m_sampleCount = sampleCount;
			m_sampleQuality = sampleQuality;
		}

		void RasterizerPipeline::SetRenderTargetCount(uint32_t renderTargetCount)
		{
			m_renderTargetCount = renderTargetCount;
		}

		void RasterizerPipeline::SetRenderTargetFormat(ResourceFormat format, int32_t index)
		{
			if (index < 0)
			{
				for (uint32_t i = 0; i < 8; ++i)
				{
					m_renderTargetFormats[i] = format;
				}
			}
			else
			{
				m_renderTargetFormats[index] = format;
			}
		}

		void RasterizerPipeline::SetDepthStencilFormat(ResourceFormat format)
		{
			m_depthStencilFormat = format;
		}
		
		void RasterizerPipeline::Create()
		{
			auto device = GetD3D12Device();
			RasterizerPipelineDesc desc = {};
			desc.blendState = m_blendState;
			desc.depthStencil = m_depthStencilState;
			desc.inputLayout = m_inputLayout;
			if (m_vertexShader)
			{
				desc.vertexShader = m_vertexShader->GetInterface();
			}
			if (m_pixelShader)
			{
				desc.pixelShader = m_pixelShader->GetInterface();
			}
			if (m_domainShader)
			{
				desc.domainShader = m_domainShader->GetInterface();
			}
			if (m_geometryShader)
			{
				desc.geometryShader = m_geometryShader->GetInterface();
			}
			if (m_hullShader)
			{
				desc.hullShader = m_hullShader->GetInterface();
			}
			desc.rasterizerState = m_rasterizerState;
			desc.sampleCount = m_sampleCount;
			desc.sampleQuality = m_sampleQuality;
			desc.topology = m_topology;
			desc.renderTargetCount = m_renderTargetCount;
			for (uint32_t i = 0; i < 8; ++i)
			{
				desc.renderTargetFormats[i] = m_renderTargetFormats[i];
			}
			desc.rootSignature = m_rootSignature->GetInterface();
			desc.depthStencilFormat = m_depthStencilFormat;
			desc.sampleMask = m_sampleMask;
			desc.nodeMask = m_nodeMask;
			m_interface = device->CreateRasterizerPipeline(desc);
		}

		IRasterizerPipeline* RasterizerPipeline::GetInterface() const
		{
			return m_interface;
		}

		RootSignature* RasterizerPipeline::GetRootSignature() const
		{
			return m_rootSignature;
		}

		Shader* RasterizerPipeline::GetVertexShader() const
		{
			return m_vertexShader;
		}
		
		Shader* RasterizerPipeline::GetPixelShader() const
		{
			return m_pixelShader;
		}
	}
}