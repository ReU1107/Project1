#pragma once
#include "IPipeline.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRaytracingPipeline : public IPipeline
		{
		public:
			virtual void* GetShaderIdentifier(const wchar_t* shaderName) const = 0;

		};
	}
}