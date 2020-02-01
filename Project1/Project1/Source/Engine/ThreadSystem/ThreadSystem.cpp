#include "ThreadSystem.h"
#include "ThreadGroup.h"
#include "RequestManager.h"

namespace Engine
{
	namespace ThreadSystem
	{
		void Startup(int32_t threadCount)
		{
			SingleRequestManager::Startup();
			SingleThreadGroup::Startup();
		}

		void WaitAll()
		{
			SingleThreadGroup::GetPtr()->WaitAll();
		}

		void Shutdown()
		{
			SingleThreadGroup::Shutdown();
			SingleRequestManager::Shutdown();
		}
	}
}
