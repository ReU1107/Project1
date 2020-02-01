#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class FillType : uint8_t;
		enum class CullType : uint8_t;
		enum class ConservativeMode : uint8_t;

		struct RasterizerDesc
		{
			int32_t depthBias;					// 深度値バイアス
			float depthBiasClamp;				// 
			float slopeScaledDepthBias;			// 
			uint32_t forcedSampleCount;			// 

			FillType fillType;					// 塗りつぶし方法
			CullType cullType;					// カリング方法
			bool frontCounterClockwise;			// 前面を半時計周りにする
			bool depthClipEnable;				// 
			bool multisampleEnable;				// 
			bool antialiasedLineEnable;			// 
			ConservativeMode conservativeMode;	// 

			static RasterizerDesc Default();

		};

	}
}