#include "D3D12RasterizerPipeline.h"
#include <d3d12.h>

namespace Engine
{
	namespace  GraphicsSystem
	{
		D3D12RasterizerPipeline::D3D12RasterizerPipeline()
			: m_native(nullptr)
		{
		}

		D3D12RasterizerPipeline::~D3D12RasterizerPipeline()
		{
			m_native->Release();
		}
		
		void* D3D12RasterizerPipeline::GetNativePipeline() const
		{
			return m_native;
		}
	}
}
