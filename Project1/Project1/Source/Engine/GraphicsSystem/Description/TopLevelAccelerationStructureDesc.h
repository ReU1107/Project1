#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		struct SubTopLevelAccelerationStructureDesc;

		struct TopLevelAccelerationStructureDesc
		{
			SubTopLevelAccelerationStructureDesc* descs;	// �f�X�N
			uint32_t bottomCount;							// ��
		};
	}
}