#pragma once

namespace Engine 
{

	namespace AudioSystem 
	{
		// �O���錾
		class IAudioEvent;

		class IAudioCallback
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~IAudioCallback(){}
			// �C�x���g����
			virtual void ReceiveEvent(IAudioEvent* audioEvent) = 0;

		};

	}

}