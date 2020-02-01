#include "RenderTargetBlendDesc.h"
#include "..//Enumerations/BlendFactor.h"
#include "..//Enumerations/BlendOperation.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		RenderTargetBlendDesc RenderTargetBlendDesc::Default()
		{
			RenderTargetBlendDesc desc = {};
			desc.blendEnable = false;
			desc.logicOperationEnable = false;
			desc.renderTargetWriteMask = 0xf;
			return desc;
		}

		RenderTargetBlendDesc RenderTargetBlendDesc::AlphaBlend()
		{
			RenderTargetBlendDesc desc = {};
			desc.blendEnable = true;
			desc.logicOperationEnable = false;
			desc.renderTargetWriteMask = 0xf;
			desc.alphaBlendOperation = BlendOperation::Addition;
			desc.colorBlendOperation = BlendOperation::Addition;
			desc.sourceColorBlendFactor = BlendFactor::One;
			desc.sourceAlphaBlendFactor = BlendFactor::One;
			desc.destinationColorBlendFactor = BlendFactor::InverseSourceAlpha;
			desc.destinationAlphaBlendFactor = BlendFactor::InverseSourceAlpha;
			return desc;
		}

	}
}
