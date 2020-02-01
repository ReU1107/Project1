#include "BlendDesc.h"
namespace Engine
{
	namespace GraphicsSystem
	{
		BlendDesc BlendDesc::NoBlend()
		{
			BlendDesc desc = {};
			desc.independentBlendEnable = false;
			desc.alphaToCoverageEnable = false;
			desc.renderTargets[0].blendEnable = false;

			return desc;
		}
	}
}