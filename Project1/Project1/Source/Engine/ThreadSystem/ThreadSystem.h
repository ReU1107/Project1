#pragma once
#include <cstdint>

namespace Engine
{
	namespace ThreadSystem
	{
		// ŠJn
		void Startup(int32_t threadCount = -1);

		void WaitAll();

		// I—¹
		void Shutdown();
	}
}