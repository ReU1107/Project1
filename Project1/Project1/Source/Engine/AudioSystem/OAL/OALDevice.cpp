#include "OALDevice.h"
//#include <al.h>
//#include <alc.h>
#if _WIN32
//#pragma comment(lib,"OpenAL32.lib")
#else // WIN64
#pragma comment(lib,"OpenAL64.lin")
#endif

/*
�݌v�͂炭����
�����I�ɂ�XAudio2����邱�Ƃ�����
�T���v�����O�f�v�X��������Ă���Ȃ�

*/

namespace Engine {

	namespace AudioSystem {

		//OALDevice::OALDevice()
		//{
		//	ALCdevice * device = alcOpenDevice(nullptr);
		//	ALCcontext* context = alcCreateContext(device, nullptr);
		//	alcMakeContextCurrent(context);

		//	
		//}

		//OALDevice::~OALDevice()
		//{
		//	//alcDestroyContext(context);
		//	//alcCloseDevice(device);
		//	// �r�b�g�ɏ�����������ł�?????
		//	//ALchar ap;
		//	//ALCchar b;
		//}
	}
}