#include "DepthStencilDesc.h"
#include "..//Enumerations/ComparisonFunction.h"
#include "..//Enumerations/DepthWriteMask.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		DepthStencilDesc DepthStencilDesc::Default()
		{
			DepthStencilDesc desc = {};
			desc.depthEnable = true;
			desc.depthFunction = ComparisonFunction::Less;
			desc.depthWriteMask = DepthWriteMask::All;
			desc.stencilEnable = false;
			return desc;
		}

	}
}
