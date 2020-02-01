#include "DXA2.h"
#include <assert.h>
#include "DXA2/DXA2Device.h"

namespace Engine
{
	namespace AudioSystem
	{
		static DXA2Device* s_device = nullptr;

		bool isStartup = false;
		void Startup()
		{
			assert(!isStartup, "オーディオシステムは既に起動中です");

			s_device = new DXA2Device();

			isStartup = true;
		}

		DXA2Device* GetDevice()
		{
			return s_device;
		}

		void Shutdown()
		{
			assert(isStartup, "オーディオシステムは既に停止中です");

			delete s_device;

			isStartup = false;

		}
	}
}