#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class IPipeline
		{
		public:
			virtual ~IPipeline() {}

			virtual void* GetNativePipeline() const = 0;
		};

	}
}