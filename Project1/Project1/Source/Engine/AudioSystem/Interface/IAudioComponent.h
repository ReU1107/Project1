#pragma once
#include <cstdint>
#include "IUnknown.h"

/*
�����𑀍삷��
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		// �O���錾
		class IAudioEffect;

		class IAudioComponent //: public IUnknown
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~IAudioComponent() {}
			// �჌�x��API���|�C���^�擾
			virtual void* GetNativeVoice() const = 0;

			// �G�t�F�N�g�ݒ�
			virtual void SetEffects(IAudioEffect* effects[], uint32_t count) = 0;

		};

	}

}