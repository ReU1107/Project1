#pragma once
#include "../Interface/IAudioDevice.h"

/*
�ꉞOpenAL�p
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