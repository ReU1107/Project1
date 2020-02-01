#pragma once
#include <cstdint>
#include "../../Math/Matrix4x4.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IAccelerationStructure;
		enum class SubTopLevelAccelerationStructureFlags : uint8_t;

		struct SubTopLevelAccelerationStructureDesc
		{
			IAccelerationStructure* bottom;					// 使用する形状
			Matrix4x4 matrix;								// 使用する行列
			uint32_t id;									// 識別番号(24bit)
			uint32_t contribution;							// シェーダーレコード番号
			uint8_t mask = 0xff;							// マスク値(8bit)
			SubTopLevelAccelerationStructureFlags flags;	// フラグ(8bit)
		};
	}
}