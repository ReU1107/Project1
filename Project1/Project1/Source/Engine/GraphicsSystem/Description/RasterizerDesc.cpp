#include "RasterizerDesc.h"
#include "..//Enumerations/FillType.h"
#include "..//Enumerations/CullType.h"
#include "..//Enumerations/ConservativeMode.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		RasterizerDesc RasterizerDesc::Default()
		{
			RasterizerDesc desc = {};
			desc.fillType = FillType::Solid;
			desc.cullType = CullType::Back;
			desc.antialiasedLineEnable = false;
			desc.conservativeMode = ConservativeMode::Off;
			desc.depthBias = 0.0f;
			desc.depthBiasClamp = 0.0f;
			desc.depthClipEnable = false;
			desc.forcedSampleCount = 0;
			desc.frontCounterClockwise = false;
			desc.multisampleEnable = false;
			desc.slopeScaledDepthBias = 0.0f;

			return desc;
		}

	}
}

