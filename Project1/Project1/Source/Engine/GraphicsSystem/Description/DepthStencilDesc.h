#pragma once
#include "DepthStencilOperationDesc.h"
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 
		enum class DepthWriteMask : uint8_t;
		enum class ComparisonFunction : uint8_t;
		enum class StencilOperation : uint8_t;

		struct DepthStencilDesc
		{
			bool depthEnable;
			DepthWriteMask depthWriteMask;
			ComparisonFunction depthFunction;
			bool stencilEnable;
			uint8_t stencilReadMask;
			uint8_t stencilWriteMask;
			DepthStencilOperationDesc frontFace;
			DepthStencilOperationDesc backFace;

			static DepthStencilDesc Default();
		};

	}
}