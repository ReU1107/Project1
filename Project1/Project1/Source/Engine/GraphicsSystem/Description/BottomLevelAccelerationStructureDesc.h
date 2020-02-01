#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		struct SubBottomLevelAccelerationStructureDesc;
		enum class BottomLevelAccelerationStructureFlags : uint8_t;
		enum class BottomLevelAccelerationBuildFlags : uint8_t;

		struct BottomLevelAccelerationStructureDesc
		{
			SubBottomLevelAccelerationStructureDesc* subDescs;
			uint32_t subCount;
			BottomLevelAccelerationStructureFlags flags;
			BottomLevelAccelerationBuildFlags buildFlags;	// ビルドフラグ
		};
	}
}