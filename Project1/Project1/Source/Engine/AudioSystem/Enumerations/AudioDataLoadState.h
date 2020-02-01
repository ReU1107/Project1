#pragma once
#include <cstdint>

namespace Engine
{

	namespace AudioSystem 
	{
	
		// �ǂݍ��ݏ�
		enum class AudioDataLoadState : uint8_t
		{
			Unloaded,	// �ǂݍ��܂ꂽ�I�[�f�B�I�f�[�^�������A���[�f�B���O���܂��J�n����Ă��Ȃ� AudioClip �Ɋւ��� AudioClip.loadState �ɂ���ĕԂ����l�ł��B
			Loading,	// ���݃I�[�f�B�I�f�[�^�����[�f�B���O���� AudioClip �Ɋւ��� AudioClip.loadState ���Ԃ��l�ł��B
			Loaded,		// �I�[�f�B�I�f�[�^�̃��[�f�B���O�ɐ������� AudioClip �Ɋւ��� AudioClip.loadState ���Ԃ��l�ł��B
			Failed,		// �I�[�f�B�I�f�[�^�̃��[�f�B���O�Ɏ��s���� AudioClip �Ɋւ��� AudioClip.loadState ���Ԃ��l�ł��B
		};
	}
}