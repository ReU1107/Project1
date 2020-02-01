#include "SceneManagement.h"
#include "SceneManager.h"

namespace Engine
{
	namespace SceneManagement
	{
		SceneManager* s_manager = nullptr;

		void Startup()
		{
			s_manager = new SceneManager();
		}

		void Shutdown()
		{
			delete s_manager;
		}
	}
}
