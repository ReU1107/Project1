#include "RootSignature.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "../Interface/IRootSignature.h"
#include "../Shader/Shader.h"
#include "SamplerState.h"
#include <d3d12.h>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		RootSignature::RootSignature()
			: m_interface(nullptr)
			, m_shader(nullptr)
			, m_type()
			, m_flags()
		{

		}

		RootSignature::~RootSignature()
		{
			delete m_interface;
		}

		void RootSignature::SetFlags(RootSignatureFlags flags)
		{
			m_flags = flags;
		}

		void RootSignature::SetType(RootSignatureType type)
		{
			m_type = type;
		}

		void RootSignature::AddLayout(const ShaderResourceLayoutDesc& desc)
		{
			m_layouts.push_back(desc);
		}

		void RootSignature::AddDescriptorTableLayout(ShaderResourceParameterDesc* parameters, uint32_t count, ShaderType usedShader)
		{
			ShaderResourceLayoutDesc layout = {};

			layout.layoutType = ShaderResourceLayoutType::DescriptorTable;
			layout.shaderType = usedShader;
			layout.descriptorTable.parameterCount = count;
			layout.descriptorTable.parameters = parameters;

			this->AddLayout(layout);
		}

		void RootSignature::AddConstantsLayout(const ShaderResourceConstantsDesc& constants, ShaderType usedShader)
		{
			ShaderResourceLayoutDesc layout = {};
			layout.constans = constants;
			layout.shaderType = usedShader;
			layout.layoutType = ShaderResourceLayoutType::Constants;

			this->AddLayout(layout);
		}

		void RootSignature::AddDescriptorLayout(const ShaderResourceDescriptorDesc& descriptor, ShaderType usedShader)
		{
			ShaderResourceLayoutDesc layout = {};
			layout.descriptor = descriptor;
			layout.shaderType = usedShader;
			layout.layoutType = ShaderResourceLayoutType::Descriptor;

			this->AddLayout(layout);
		}

		void RootSignature::AddRange(uint32_t parameterCount, ShaderType usedShader)
		{
			ShaderResourceRange range = {};
			range.parameters = new ShaderResourceParameterDesc[parameterCount];
			range.count = parameterCount;
			range.usedShader = usedShader;

			m_ranges.push_back(range);
		}

		void RootSignature::AddConstantBufferView(uint32_t index, uint32_t space, ShaderType usedShader)
		{
			ShaderResourceDescriptorDesc desc = {};
			desc.index = index;
			desc.space = space;
			desc.type = ShaderResourceType::ConstantBuffer;

			AddDescriptorLayout(desc, usedShader);
		}

		void RootSignature::AddConstantBufferViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count, uint32_t space, uint32_t offset)
		{
			auto& range = m_ranges[rangeIndex];
			auto& parameter = range.parameters[range.index++];

			parameter.index = registerIndex;
			parameter.count = count;
			parameter.space = space;
			parameter.type = ShaderResourceType::ConstantBuffer;

		}

		void RootSignature::AddShaderResourceView(uint32_t index, uint32_t space, ShaderType usedShader)
		{
			ShaderResourceDescriptorDesc desc = {};
			desc.index = index;
			desc.space = space;
			desc.type = ShaderResourceType::ShaderResource;

			AddDescriptorLayout(desc, usedShader);
		}

		void RootSignature::AddShaderResourceViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count, uint32_t space, uint32_t offset)
		{
			auto& range = m_ranges[rangeIndex];
			auto& parameter = range.parameters[range.index++];

			parameter.index = registerIndex;
			parameter.count = count;
			parameter.space = space;
			parameter.type = ShaderResourceType::ShaderResource;
		}

		void RootSignature::AddUnorderedAccessView(uint32_t index, uint32_t space, ShaderType usedShader)
		{
			ShaderResourceDescriptorDesc desc = {};
			desc.index = index;
			desc.space = space;
			desc.type = ShaderResourceType::ReadWriteResource;

			AddDescriptorLayout(desc, usedShader);
		}

		void RootSignature::AddUnorderedAccessViewInRanges(uint32_t registerIndex, uint32_t rangeIndex, uint32_t count, uint32_t space, uint32_t offset)
		{
			auto& range = m_ranges[rangeIndex];
			auto& parameter = range.parameters[range.index++];

			parameter.index = registerIndex;
			parameter.count = count;
			parameter.space = space;
			parameter.type = ShaderResourceType::ReadWriteResource;
		}

		void RootSignature::AddStaticSamplerState()
		{
			SamplerState state = {};
			m_staticSampler.push_back(state);
		}

		void RootSignature::SetShader(Shader* shader)
		{
			m_shader = shader;
		}

		void RootSignature::Create()
		{
			RootSignatureDesc desc = {};
			if (m_shader)
			{
				desc.isShader = true;
				desc.shader = m_shader->GetInterface();
			}
			else
			{
				for (auto& range : m_ranges)
				{
					AddDescriptorTableLayout(range.parameters, range.count, range.usedShader);
				}

				desc.staticSampler = m_staticSampler.size() > 0 ? true : false;
				desc.layoutCount = (uint32_t)m_layouts.size();
				desc.layouts = m_layouts.data();
				desc.flags = m_flags;
				desc.isShader = false;
			}

			m_interface = GetD3D12Device()->CreateRootSignature(desc);
		}

		IRootSignature* RootSignature::GetInterface() const
		{
			return m_interface;
		}

		RootSignatureType RootSignature::GetType() const
		{
			return m_type;
		}

		void RootSignature::SetName(const std::wstring& name)
		{
			ID3D12RootSignature* signature = (ID3D12RootSignature*)m_interface->GetNativeSignature();
			signature->SetName(name.c_str());
		}
	}

}