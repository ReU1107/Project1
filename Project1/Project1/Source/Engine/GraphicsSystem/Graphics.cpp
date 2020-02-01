#include "Graphics.h"
#include "D3D12/D3D12Device.h"
#include "D3D12.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		Graphics::Graphics()
			: m_device(nullptr)
		{
		}

		Graphics::~Graphics()
		{
			delete m_device;
		}

		void Graphics::CreateDefaultTexture()
		{

		}
	}
}