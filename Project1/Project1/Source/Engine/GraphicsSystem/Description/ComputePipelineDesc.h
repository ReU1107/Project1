#pragma once
#include <d3d12.h>
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRootSignature;
		class IShader;

		struct ComputePipelineDesc
		{
			IRootSignature* rootSignature;			// ルートシグネチャ
			IShader* computeShader;					// コンピュートシェーダー
			uint32_t nodeMask;
		};

	}
}
