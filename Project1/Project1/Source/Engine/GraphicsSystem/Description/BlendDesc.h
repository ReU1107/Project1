#pragma once
#include "RenderTargetBlendDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		struct BlendDesc
		{
			bool alphaToCoverageEnable = false;		// アルファトゥカバレッジ
			bool independentBlendEnable = false;	// レンダーターゲット毎に切り替えるか
			RenderTargetBlendDesc renderTargets[8];	// レンダーターゲット

			static BlendDesc NoBlend();
		};
	}
}