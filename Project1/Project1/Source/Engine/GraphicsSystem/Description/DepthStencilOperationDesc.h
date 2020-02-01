#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class ComparisonFunction : uint8_t;
		enum class StencilOperation : uint8_t;

		struct DepthStencilOperationDesc
		{
			StencilOperation stencilFailOperation;
			StencilOperation stencilDepthFailOperation;
			StencilOperation stencilPassOperation;
			ComparisonFunction stencilFunction;
		};
	}
}