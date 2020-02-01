#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BlendFactor : uint8_t
		{
			Zero,						// (0,0,0,0)
			One,						// (1,1,1,1)
			SourceColor,				// (Sr,Sg,Sb,Sa)
			InverseSourceColor,			// (1-Sr,1-Sg,1-Sb,1-Sa)
			SourceAlpha,				// (Sa,Sa,Sa,Sa)
			InverseSourceAlpha,			// (1-Sa,1-Sa,1-Sa,1-Sa)
			DestinationColor,			// (Dr,Dg,Db,Da)
			InverseDestinationColor,	// (1-Dr,1-Dg,1-Db,1-Da)
			DestinationAlpha,			// (Da,Da,Da,Da)
			InverseDestinationAlpha,	// (1-Da,1-Da,1-Da,1-Da)
			SourceAlphaSaturate,		// (f、f、f、1)f = min(Sa、1-Da)
			PresetFactor,				// 
			InversePresetFactor,		// 
			// よくわからん
			//D3D12_BLEND_SRC1_COLOR = 16,
			//D3D12_BLEND_INV_SRC1_COLOR = 17,
			//D3D12_BLEND_SRC1_ALPHA = 18,
			//D3D12_BLEND_INV_SRC1_ALPHA = 19
		};
	}
}