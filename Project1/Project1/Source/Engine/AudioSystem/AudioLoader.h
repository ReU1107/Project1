#pragma once
#include <string>
#include <cstdint>

/*
�I�[�v���֐��͈�x�����ǂݍ��݂��s��
*/

namespace Engine 
{

	namespace AudioSystem 
	{
		class AudioClip;
		class AudioBuffer;
		/*
		�I�[�f�B�I�f�[�^(PCM�o�b�t�@)�ǂݍ��݃N���X
		*/
		class AudioLoader
		{

		public:

			virtual std::shared_ptr<AudioClip> Open(const std::string& filePath) = 0;

			virtual void LoadBuffer(std::shared_ptr<AudioBuffer> buffer, int32_t size = -1) = 0;

		};

	}

}