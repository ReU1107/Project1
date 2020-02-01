#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ResourceFormat : uint8_t
		{
			RGBA32UInt,
			RGBA32SInt,
			RGBAFloat,
			RGBAHalf,
			RGBAUnorm,
			RGBFloat,
			RGFloat,
			RFloat,
			RGHalf,
			RHalf,
			Depth32,
			Depth16,
			Depth24Stencil8,
			RGB10A2Unorm,
			//Alpha8,				// アルファのみのテクスチャ
			//ARGB4444,			// 1 ピクセル 16 ビットのテクスチャ形式 アルファチャンネルが適用されています
			//RGB24,				// Color texture format, 8 - bits per channel.
			//RGBA32,				// 1 チャンネルあたり 8 ビットで構成されたアルファチャンネルを持つカラーのテクスチャ形式
			//ARGB32,				// 1 チャンネルあたり 8 ビットで構成されたアルファチャンネルを持つカラーのテクスチャ形式
			//RGB565,				// 16 ビットカラーのテクスチャ形式
			//R16,				// Single channel(R) texture format, 16 bit integer.
			//DXT1,				// 圧縮されたテクスチャ形式
			//DXT5,				// 圧縮されたアルファが適用されているテクスチャ形式
			//RGBA4444,			// 1 チャンネルあたり 4 ビットで構成されたアルファチャンネルを持つ色のテクスチャ形式
			//RHalf,				// スカラー値(R) のテクスチャ形式 16 ビットの浮動小数点
			//RGHalf,				// 2 色(RG) のテクスチャ形式 各チャンネル 16 ビットの浮動小数点
			//RGBAHalf,			// RGB カラーとアルファチャンネルのテクスチャ形式 各チャンネルは 16 ビットの浮動小数点
			//RFloat,				// スカラー値(R) のテクスチャ形式 32 ビットの浮動小数点
			//RGFloat,			// 2 色(RG) のテクスチャ形式 各チャンネル 32 ビットの浮動小数点
			//RGBAFloat,			// RGB color and alpha texture format, 32 - bit floats per channel.
			//RG16,				// Two color(RG) texture format, 8 - bits per channel.
			//R8,					// Single channel(R) texture format, 8 bit integer.
		};

	}

}

/*
			YUY2,				// A format that uses the YUV color space and is often used for video encoding or playback.
			RGB9e5Float,		// RGB HDR format, with 9 bit mantissa per channel and a 5 bit shared exponent.
			BC4,				// Compressed one channel(R) texture format.
			BC5,				// Compressed two - channel(RG) texture format.
			BC6H,				// HDR compressed color texture format.
			BC7,				// High quality compressed color texture format.
			DXT1Crunched,		// Compressed color texture format with Crunch compression for smaller storage sizes.
			DXT5Crunched,		// Compressed color with alpha channel texture format with Crunch compression for smaller storage sizes.
			PVRTC_RGB2,			// 1ピクセル2ビットの圧縮されたテクスチャ形式（ iOS 専用）
			PVRTC_RGBA2,		// 1ピクセル2ビットのアルファが適用されている、圧縮されたテクスチャ形式
			PVRTC_RGB4,			// 1ピクセル4ビットの圧縮されたテクスチャ形式（ iOS 専用）
			PVRTC_RGBA4,		// 1ピクセル4ビットのアルファが適用されている、圧縮されたテクスチャ形式
			ETC_RGB4,			// 1ピクセル4ビットの圧縮されたテクスチャ形式（ OpenGL ES 2.0 専用）
			EAC_R,				// 1ピクセルにつき4ビットで圧縮された符号なしシングルチャンネルテクスチャ形式の ETC2 / EAC(GL ES 3.0 専用)
			EAC_R_SIGNED,		// 1ピクセルにつき4ビットで圧縮された符号ありシングルチャンネルテクスチャ形式の ETC2 / EAC(GL ES 3.0 専用)
			EAC_RG,				// 1ピクセルにつき8ビットで圧縮された符号なしデュアルチャンネル(RB) テクスチャ形式の ETC2 / EAC(GL ES 3.0 専用)
			EAC_RG_SIGNED,		// 1ピクセルにつき8ビットで圧縮された符号ありデュアルチャンネル(RB) テクスチャ形式の ETC2 / EAC(GL ES 3.0 専用)
			ETC2_RGB,			// ETC2(GL ES 3.0 用) による各ピクセル4ビットの圧縮 RGB テクスチャ形式。
			ETC2_RGBA1,			// ETC2(GL ES 3.0 用) による各ピクセル4ビットの RGB チャンネル と、1ビットのアルファチャンネルを持つテクスチャ形式
			ETC2_RGBA8,			// ETC2(GL ES 3.0 用) による各ピクセル8ビットの圧縮 RGBA テクスチャ形式
			ASTC_RGB_4x4,		// ASTC(128 ビットに 4x4 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGB_5x5,		// ASTC(128 ビットに 5x5 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGB_6x6,		// ASTC(128 ビットに 6x6 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGB_8x8,		// ASTC(128 ビットに 8x8 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGB_10x10,		// ASTC(128 ビットに 10x10 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGB_12x12,		// ASTC(128 ビットに 12x12 ピクセルブロックを並べる) により圧縮された RGB テクスチャ形式
			ASTC_RGBA_4x4,		// ASTC(128 ビットに 4x4 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
			ASTC_RGBA_5x5,		// ASTC(128 ビットに 5x5 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
			ASTC_RGBA_6x6,		// ASTC(128 ビットに 6x6 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
			ASTC_RGBA_8x8,		// ASTC(128 ビットに 8x8 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
			ASTC_RGBA_10x10,	// ASTC(128 ビットに 10x10 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
			ASTC_RGBA_12x12,	// ASTC(128 ビットに 12x12 ピクセルブロックを並べる) により圧縮された RGBA テクスチャ形式
*/