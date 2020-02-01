#include "GraphicsPass.h"
#include "..//HardwareBuffer/ResourceDescriptor.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		GraphicsPass::GraphicsPass()
			: m_shaderResourceDescriptor(nullptr)
			, m_isActive(true)
		{
		}

		GraphicsPass::~GraphicsPass()
		{
			delete m_shaderResourceDescriptor;
		}

		void GraphicsPass::Active(bool active)
		{
			m_isActive = active;
		}
	}

}