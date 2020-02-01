#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		enum class ResourceFlags : uint8_t;
		enum class ResourceFormat : uint8_t;
		enum class ResourceDimension : uint8_t;
		enum class ResourceStates : uint16_t;

		struct TextureDesc
		{
			uint32_t width;					// 幅
			uint32_t height;				// 高さ
			union {
				uint32_t arrayCount;
				uint32_t depth;
			};
			uint32_t mipLevel;				// ミップマップレベル
			uint32_t multiSampleCount;		// マルチサンプルカウント
			uint32_t multiSampleQuality;	// マルチサンプルクオリティ
			ResourceStates states;			// リソースの初期状態
			ResourceDimension dimension;	// リソースの次元
			ResourceFlags flags;			// フラグ
			ResourceFormat format;			// フォーマット
			union
			{
				float color[4];				// 
				struct
				{
					float depth;			// 
					uint8_t stencil;		// 
				};

			}clearValue;					// 

			static TextureDesc Default2D(uint32_t width, uint32_t height, ResourceFormat format, bool renderTarget = false, bool depthStencil = false, bool unorderedAccess = false, bool shaderResource = true);
		};


	}

}