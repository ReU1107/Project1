#pragma once

struct IUnknown;

namespace Engine
{

	namespace AudioSystem
	{

		class DXA2ReverbEffect
		{
		private:
			IUnknown* m_nativeEffect;

		public:
			DXA2ReverbEffect();
		};

	}

}