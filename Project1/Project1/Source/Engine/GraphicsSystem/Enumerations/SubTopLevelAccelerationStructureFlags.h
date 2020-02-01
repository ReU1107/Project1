#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class SubTopLevelAccelerationStructureFlags : uint8_t
		{
			None = 0x00,					// 指定なし
			CullDisable = 0x01,				// カリングの影響を受けない
			FrontCounterClockwise = 0x02,	// 前面が左回りの配置の頂点になる
			Opaque = 0x04,					// 不透明
			NonOpaque = 0x08,				// 不透明じゃない
		};
	}
}