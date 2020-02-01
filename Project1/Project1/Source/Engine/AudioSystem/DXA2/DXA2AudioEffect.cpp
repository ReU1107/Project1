#include "DXA2AudioEffect.h"
#include <xaudio2fx.h>
#include <xapo.h>

namespace Engine
{

	namespace AudioSystem 
	{

		DXA2AudioEffect::DXA2AudioEffect()
			: base()
			, m_nativeEffect(nullptr)
		{
			
		}

		DXA2AudioEffect::~DXA2AudioEffect()
		{
			m_nativeEffect->Release();
		}

		void* DXA2AudioEffect::GetNativeEffect() const
		{
			return m_nativeEffect;
		}
	}
}
