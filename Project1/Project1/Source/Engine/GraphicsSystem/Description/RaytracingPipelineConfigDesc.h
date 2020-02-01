#pragma once
#include <cstdint>

/*
D3D12_RAYTRACING_PIPELINE_CONFIG
*/

namespace Engine 
{

	namespace GraphicsSystem
	{

		// レイトレーシングパイプライン情報
		struct RaytracingPipelineConfigDesc
		{
			uint32_t raytraceMaxCount;
		};

	}

}

