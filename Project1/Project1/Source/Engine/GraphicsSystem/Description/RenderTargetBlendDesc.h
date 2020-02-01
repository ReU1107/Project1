#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class BlendOperation : uint8_t;
		enum class BlendFactor : uint8_t;
		enum class LogicOperation : uint8_t;

		struct RenderTargetBlendDesc
		{
			bool blendEnable;
			bool logicOperationEnable;
			BlendFactor sourceColorBlendFactor;			// 合成しようとしている色に掛ける係数
			BlendOperation colorBlendOperation;			// RGBのブレンド方法(計算方法)
			BlendFactor destinationColorBlendFactor;	// 既にある色に掛ける係数

			BlendFactor sourceAlphaBlendFactor;			// 合成しようとしているアルファ値に掛ける係数
			BlendOperation alphaBlendOperation;			// アルファ値のブレンド方法(計算方法)
			BlendFactor destinationAlphaBlendFactor;	// 既にあるアルファ値に掛ける係数

			LogicOperation logicOperation;				// 
			uint8_t renderTargetWriteMask;				// 
			static RenderTargetBlendDesc Default();
			static RenderTargetBlendDesc AlphaBlend();
		};
	}
}