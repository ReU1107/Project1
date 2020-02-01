#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{
		struct RaytracingPipelineParameterDesc;

		struct RaytracingPipelineDesc
		{
			RaytracingPipelineParameterDesc* parameters;	// サブステート配列
			uint32_t parameterCount;						// ステート数
		};

	}

}