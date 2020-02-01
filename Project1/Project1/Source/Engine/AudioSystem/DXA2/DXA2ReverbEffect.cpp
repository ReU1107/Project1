#include "DXA2ReverbEffect.h"
#include <xaudio2fx.h>
#include <xapofx.h>
#include <xapo.h>

namespace Engine 
{

	namespace AudioSystem
	{
		DXA2ReverbEffect::DXA2ReverbEffect()
			: m_nativeEffect(nullptr)
		{
			XAudio2CreateReverb(&m_nativeEffect);
		}
	}
}