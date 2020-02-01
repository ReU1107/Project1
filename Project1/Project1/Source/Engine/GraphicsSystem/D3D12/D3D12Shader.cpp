#include "D3D12Shader.h"
#include <d3d12.h>

namespace Engine 
{
	namespace GraphicsSystem 
	{

		D3D12Shader::D3D12Shader()
			: m_blob(nullptr)
		{
		}

		D3D12Shader::~D3D12Shader()
		{
			m_blob->Release();
		}

		void* D3D12Shader::GetNativeShader() const
		{
			return m_blob;
		}

		void* D3D12Shader::GetBuffer() const
		{
			return m_blob->GetBufferPointer();
		}

		uint64_t D3D12Shader::GetSize() const
		{
			return m_blob->GetBufferSize();
		}
	}
}
