#pragma once
#include <cstdint>

namespace Engine
{

	// �𑜓x�^�C�v(�w�肷��ƃf�t�H���g�̉𑜓x�ɂȂ�)
	enum class ShadowResolutionType : uint8_t
	{
		None,
		Low,				// ��𑜓x
		Medium,				// ���𑜓x
		QualitySettings,	// �f�t�H���g�ݒ�
		High,				// ���𑜓x
		VeryHigh			// ���ɍ����𑜓x
	};

	// �V���h�E�}�b�v�̉𑜓x(enum class�������l�����ݒ�ł��Ȃ���)
	struct ShadowResolution
	{
		static constexpr float Low = 0.5f;				// ��𑜓x
		static constexpr float Medium = 0.75f;			// ���𑜓x
		static constexpr float QualitySettings = 1.0f;	// �f�t�H���g�ݒ�
		static constexpr float High = 2.0f;				// ���𑜓x
		static constexpr float VeryHigh = 4.0f;			// ���ɍ����𑜓x
	};
}