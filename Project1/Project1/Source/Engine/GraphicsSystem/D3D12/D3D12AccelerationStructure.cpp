#include "D3D12AccelerationStructure.h"
#include <d3d12.h>

namespace Engine
{
	namespace GraphicsSystem
	{
		D3D12AccelerationStructure::D3D12AccelerationStructure()
			: m_result(nullptr)
			, m_scratch(nullptr)
			, m_update(nullptr)
		{
		}

		D3D12AccelerationStructure::~D3D12AccelerationStructure()
		{
			if (m_result)
				m_result->Release();
			if (m_scratch)
				m_scratch->Release();
			if (m_update)
				m_update->Release();
		}

		void* D3D12AccelerationStructure::GetNativeResource() const
		{
			return m_result;
		}
	}
}