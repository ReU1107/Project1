#pragma once
#include "IPipeline.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRasterizerPipeline : public IPipeline
		{
		public:
			virtual ~IRasterizerPipeline() {}

		};
	}
}