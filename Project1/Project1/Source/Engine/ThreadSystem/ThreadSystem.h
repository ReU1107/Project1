#pragma once
#include <cstdint>

namespace Engine
{
	namespace ThreadSystem
	{
		// �J�n
		void Startup(int32_t threadCount = -1);

		void WaitAll();

		// �I��
		void Shutdown();
	}
}