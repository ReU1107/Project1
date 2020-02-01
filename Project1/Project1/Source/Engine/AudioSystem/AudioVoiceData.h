#pragma once
#include <cstdint>

namespace Engine 
{

	namespace AudioSystem 
	{
		enum class DigitalFormat : uint32_t;
		// 
		struct AudioVoiceData
		{
			uint32_t frequency;		// ���g��
			float maxRatio;
			DigitalFormat format;	// �t�H�[�}�b�g
			uint8_t channelCount;	// �`�����l����
			uint8_t bitDepth;		// �r�b�g��
			bool useFilter;			// �t�B���^�[���g�p����
			bool pitchShift;		// �s�b�`�V�t�g���s��
			bool sampleConversion;	// �T���v�����O���g���ϊ����s��

			AudioVoiceData();
		};

	}

}