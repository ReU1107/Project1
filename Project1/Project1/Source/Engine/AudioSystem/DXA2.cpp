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
			assert(!isStartup, "�I�[�f�B�I�V�X�e���͊��ɋN�����ł�");

			s_device = new DXA2Device();

			isStartup = true;
		}

		DXA2Device* GetDevice()
		{
			return s_device;
		}

		void Shutdown()
		{
			assert(isStartup, "�I�[�f�B�I�V�X�e���͊��ɒ�~���ł�");

			delete s_device;

			isStartup = false;

		}
	}
}