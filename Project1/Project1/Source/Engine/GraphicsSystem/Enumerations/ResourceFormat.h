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
			//Alpha8,				// �A���t�@�݂̂̃e�N�X�`��
			//ARGB4444,			// 1 �s�N�Z�� 16 �r�b�g�̃e�N�X�`���`�� �A���t�@�`�����l�����K�p����Ă��܂�
			//RGB24,				// Color texture format, 8 - bits per channel.
			//RGBA32,				// 1 �`�����l�������� 8 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������J���[�̃e�N�X�`���`��
			//ARGB32,				// 1 �`�����l�������� 8 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������J���[�̃e�N�X�`���`��
			//RGB565,				// 16 �r�b�g�J���[�̃e�N�X�`���`��
			//R16,				// Single channel(R) texture format, 16 bit integer.
			//DXT1,				// ���k���ꂽ�e�N�X�`���`��
			//DXT5,				// ���k���ꂽ�A���t�@���K�p����Ă���e�N�X�`���`��
			//RGBA4444,			// 1 �`�����l�������� 4 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������F�̃e�N�X�`���`��
			//RHalf,				// �X�J���[�l(R) �̃e�N�X�`���`�� 16 �r�b�g�̕��������_
			//RGHalf,				// 2 �F(RG) �̃e�N�X�`���`�� �e�`�����l�� 16 �r�b�g�̕��������_
			//RGBAHalf,			// RGB �J���[�ƃA���t�@�`�����l���̃e�N�X�`���`�� �e�`�����l���� 16 �r�b�g�̕��������_
			//RFloat,				// �X�J���[�l(R) �̃e�N�X�`���`�� 32 �r�b�g�̕��������_
			//RGFloat,			// 2 �F(RG) �̃e�N�X�`���`�� �e�`�����l�� 32 �r�b�g�̕��������_
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
			PVRTC_RGB2,			// 1�s�N�Z��2�r�b�g�̈��k���ꂽ�e�N�X�`���`���i iOS ��p�j
			PVRTC_RGBA2,		// 1�s�N�Z��2�r�b�g�̃A���t�@���K�p����Ă���A���k���ꂽ�e�N�X�`���`��
			PVRTC_RGB4,			// 1�s�N�Z��4�r�b�g�̈��k���ꂽ�e�N�X�`���`���i iOS ��p�j
			PVRTC_RGBA4,		// 1�s�N�Z��4�r�b�g�̃A���t�@���K�p����Ă���A���k���ꂽ�e�N�X�`���`��
			ETC_RGB4,			// 1�s�N�Z��4�r�b�g�̈��k���ꂽ�e�N�X�`���`���i OpenGL ES 2.0 ��p�j
			EAC_R,				// 1�s�N�Z���ɂ�4�r�b�g�ň��k���ꂽ�����Ȃ��V���O���`�����l���e�N�X�`���`���� ETC2 / EAC(GL ES 3.0 ��p)
			EAC_R_SIGNED,		// 1�s�N�Z���ɂ�4�r�b�g�ň��k���ꂽ��������V���O���`�����l���e�N�X�`���`���� ETC2 / EAC(GL ES 3.0 ��p)
			EAC_RG,				// 1�s�N�Z���ɂ�8�r�b�g�ň��k���ꂽ�����Ȃ��f���A���`�����l��(RB) �e�N�X�`���`���� ETC2 / EAC(GL ES 3.0 ��p)
			EAC_RG_SIGNED,		// 1�s�N�Z���ɂ�8�r�b�g�ň��k���ꂽ��������f���A���`�����l��(RB) �e�N�X�`���`���� ETC2 / EAC(GL ES 3.0 ��p)
			ETC2_RGB,			// ETC2(GL ES 3.0 �p) �ɂ��e�s�N�Z��4�r�b�g�̈��k RGB �e�N�X�`���`���B
			ETC2_RGBA1,			// ETC2(GL ES 3.0 �p) �ɂ��e�s�N�Z��4�r�b�g�� RGB �`�����l�� �ƁA1�r�b�g�̃A���t�@�`�����l�������e�N�X�`���`��
			ETC2_RGBA8,			// ETC2(GL ES 3.0 �p) �ɂ��e�s�N�Z��8�r�b�g�̈��k RGBA �e�N�X�`���`��
			ASTC_RGB_4x4,		// ASTC(128 �r�b�g�� 4x4 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGB_5x5,		// ASTC(128 �r�b�g�� 5x5 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGB_6x6,		// ASTC(128 �r�b�g�� 6x6 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGB_8x8,		// ASTC(128 �r�b�g�� 8x8 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGB_10x10,		// ASTC(128 �r�b�g�� 10x10 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGB_12x12,		// ASTC(128 �r�b�g�� 12x12 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGB �e�N�X�`���`��
			ASTC_RGBA_4x4,		// ASTC(128 �r�b�g�� 4x4 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
			ASTC_RGBA_5x5,		// ASTC(128 �r�b�g�� 5x5 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
			ASTC_RGBA_6x6,		// ASTC(128 �r�b�g�� 6x6 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
			ASTC_RGBA_8x8,		// ASTC(128 �r�b�g�� 8x8 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
			ASTC_RGBA_10x10,	// ASTC(128 �r�b�g�� 10x10 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
			ASTC_RGBA_12x12,	// ASTC(128 �r�b�g�� 12x12 �s�N�Z���u���b�N����ׂ�) �ɂ�舳�k���ꂽ RGBA �e�N�X�`���`��
*/