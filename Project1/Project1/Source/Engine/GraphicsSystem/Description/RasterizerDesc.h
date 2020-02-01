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
			int32_t depthBias;					// �[�x�l�o�C�A�X
			float depthBiasClamp;				// 
			float slopeScaledDepthBias;			// 
			uint32_t forcedSampleCount;			// 

			FillType fillType;					// �h��Ԃ����@
			CullType cullType;					// �J�����O���@
			bool frontCounterClockwise;			// �O�ʂ𔼎��v����ɂ���
			bool depthClipEnable;				// 
			bool multisampleEnable;				// 
			bool antialiasedLineEnable;			// 
			ConservativeMode conservativeMode;	// 

			static RasterizerDesc Default();

		};

	}
}