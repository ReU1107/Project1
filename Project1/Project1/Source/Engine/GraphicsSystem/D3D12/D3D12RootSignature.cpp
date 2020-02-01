#include "D3D12RootSignature.h"
#include <d3d12.h>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		D3D12RootSignature::D3D12RootSignature()
			: m_native(nullptr)
		{
		}

		D3D12RootSignature::~D3D12RootSignature()
		{
			m_native->Release();
		}

		void* D3D12RootSignature::GetNativeSignature() const
		{
			return m_native;
		}
	}
}