#pragma once

namespace Engine
{
	namespace AudioSystem
	{
		class DXA2Device;

		void Startup();

		DXA2Device* GetDevice();

		void Shutdown();
	}
}