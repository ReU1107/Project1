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
			uint32_t frequency;		// 周波数
			float maxRatio;
			DigitalFormat format;	// フォーマット
			uint8_t channelCount;	// チャンネル数
			uint8_t bitDepth;		// ビット数
			bool useFilter;			// フィルターを使用する
			bool pitchShift;		// ピッチシフトを行う
			bool sampleConversion;	// サンプリング周波数変換を行う

			AudioVoiceData();
		};

	}

}