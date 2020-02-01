#include "D3D12ComputePipeline.h"
#include <d3d12.h>

namespace Engine
{
	namespace GraphicsSystem
	{
		D3D12ComputePipeline::D3D12ComputePipeline()
			: m_native(nullptr)
		{
		}
		
		D3D12ComputePipeline::~D3D12ComputePipeline()
		{
			m_native->Release();
		}

		void* D3D12ComputePipeline::GetNativePipeline() const
		{
			return m_native;
		}
	}
}
