#include "D3D12ResourceView.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		D3D12ResourceView::D3D12ResourceView()
			: m_cpuHandle()
			, m_gpuHandle()
			, m_index(0)
			, m_isCopy(false)
		{
		}

		D3D12ResourceView::~D3D12ResourceView()
		{
		}
	}
}