#pragma once
#include "../Interface/IAudioEffect.h"

// �O���錾
struct IXAPO;

namespace Engine 
{

	namespace AudioSystem 
	{

		class DXA2AudioEffect final : public IAudioEffect
		{
		private:
			using base = IAudioEffect;
		private:
			IXAPO* m_nativeEffect;

		public:
			// �R���X�g���N�^
			DXA2AudioEffect();
			// �f�X�g���N�^
			~DXA2AudioEffect();
		public:
			// 
			virtual void* GetNativeEffect() const override;

			virtual bool IsValid() const override { return true; }
		};

	}

}
