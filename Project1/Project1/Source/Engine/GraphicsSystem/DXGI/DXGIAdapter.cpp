#include "DXGIAdapter.h"
#include <dxgi1_6.h>

namespace Engine
{
	namespace GraphicsSystem
	{
		DXGIAdapter::DXGIAdapter()
			: m_nativeAdapter(nullptr)
		{
		}

		DXGIAdapter::~DXGIAdapter()
		{
			m_nativeAdapter->Release();
		}
	}
}