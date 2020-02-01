#include "AudioVoiceData.h"
namespace Engine 
{

	namespace AudioSystem
	{
		AudioVoiceData::AudioVoiceData()
			: frequency(0.0f)
			, maxRatio(2.0f)
			, format()
			, channelCount(0)
			, bitDepth(0)
			, useFilter(true)
			, pitchShift(false)
			, sampleConversion(false)
		{
		}
	}
}