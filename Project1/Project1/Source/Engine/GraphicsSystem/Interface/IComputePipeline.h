#pragma once
#include "IPipeline.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IComputePipeline : public IPipeline
		{
		public:
			virtual ~IComputePipeline() {}

		};

	}
}