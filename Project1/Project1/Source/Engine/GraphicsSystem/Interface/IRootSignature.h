#pragma once

namespace Engine
{

	namespace GraphicsSystem 
	{

		class IRootSignature
		{
		public:
			virtual void* GetNativeSignature() const = 0;

		};
	}
}