#pragma once

/*
�I�[�f�B�I�G�t�F�N�g���g������
�V�����쐬����ꍇ�͂��̃N���X���p�����Ă�������
*/

namespace Engine 
{

	namespace AudioSystem 
	{

		class __declspec(uuid("F7972759-297C-44F5-8E54-4C5BED5A393B")) IAudioEffect
		{
		public:
			virtual ~IAudioEffect() {}

			// �჌�x��API�擾
			virtual void* GetNativeEffect() const = 0;
			
			// �L����������
			virtual bool IsValid() const = 0;
			

		};

	}

}