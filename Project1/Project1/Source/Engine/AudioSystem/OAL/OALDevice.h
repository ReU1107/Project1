#pragma once
#include "../Interface/IAudioDevice.h"

/*
ˆê‰žOpenAL—p
*/

namespace Engine {

	namespace AudioSystem {

		class OALDevice : public IAudioDevice
		{
		private:
		public:
			OALDevice();
			~OALDevice();
		};

	}
}