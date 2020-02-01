#include "D3D12RaytracingPipeline.h"
#include <d3d12.h>

namespace Engine 
{
	
	namespace GraphicsSystem 
	{

		D3D12RaytracingPipeline::D3D12RaytracingPipeline()
			: m_native(nullptr)
			, m_properties(nullptr)
		{
		}

		D3D12RaytracingPipeline::~D3D12RaytracingPipeline()
		{
			if (m_properties)
				m_properties->Release();
			if (m_native)
				m_native->Release();
		}

		void* D3D12RaytracingPipeline::GetNativePipeline() const
		{
			return m_native;
		}

		void* D3D12RaytracingPipeline::GetShaderIdentifier(const wchar_t* shaderName) const
		{
			return m_properties->GetShaderIdentifier(shaderName);
		}
	}
}