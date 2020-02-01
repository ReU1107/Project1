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
			BlendFactor sourceColorBlendFactor;			// �������悤�Ƃ��Ă���F�Ɋ|����W��
			BlendOperation colorBlendOperation;			// RGB�̃u�����h���@(�v�Z���@)
			BlendFactor destinationColorBlendFactor;	// ���ɂ���F�Ɋ|����W��

			BlendFactor sourceAlphaBlendFactor;			// �������悤�Ƃ��Ă���A���t�@�l�Ɋ|����W��
			BlendOperation alphaBlendOperation;			// �A���t�@�l�̃u�����h���@(�v�Z���@)
			BlendFactor destinationAlphaBlendFactor;	// ���ɂ���A���t�@�l�Ɋ|����W��

			LogicOperation logicOperation;				// 
			uint8_t renderTargetWriteMask;				// 
			static RenderTargetBlendDesc Default();
			static RenderTargetBlendDesc AlphaBlend();
		};
	}
}