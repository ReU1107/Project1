#pragma once
#include "IResource.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		struct TopLevelAccelerationStructureDesc;

		class IAccelerationStructure : public IResource
		{
		public:
			virtual ~IAccelerationStructure() {};

			virtual void Update(const TopLevelAccelerationStructureDesc& desc) = 0;

		};
	}
}