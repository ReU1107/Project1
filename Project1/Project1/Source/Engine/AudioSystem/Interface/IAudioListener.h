#pragma once

/*
�჌�x��AudioVoice��
AudioClip�̒l�n���I�ȃN���X
*/

namespace Engine
{

	namespace AudioSystem 
	{

		class IAudioListener
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~IAudioListener() {}

			// �o�b�t�@�������Ȃ���
			virtual void OnBufferEnd() = 0;


		};

	}

}