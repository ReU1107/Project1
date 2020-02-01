#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{
		struct RaytracingPipelineParameterDesc;

		struct RaytracingPipelineDesc
		{
			RaytracingPipelineParameterDesc* parameters;	// �T�u�X�e�[�g�z��
			uint32_t parameterCount;						// �X�e�[�g��
		};

	}

}