#pragma once
#include <xaudio2.h>
#include "../Interface/IAudioCallback.h"

namespace Engine
{

	namespace AudioSystem 
	{

		class DXA2AudioCallback : public IAudioCallback,IXAudio2VoiceCallback
		{
		private:

		};

	}

}