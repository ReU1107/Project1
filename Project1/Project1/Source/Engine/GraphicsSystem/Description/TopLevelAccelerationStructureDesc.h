#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		struct SubTopLevelAccelerationStructureDesc;

		struct TopLevelAccelerationStructureDesc
		{
			SubTopLevelAccelerationStructureDesc* descs;	// ÉfÉXÉN
			uint32_t bottomCount;							// êî
		};
	}
}