#include "OALDevice.h"
//#include <al.h>
//#include <alc.h>
#if _WIN32
//#pragma comment(lib,"OpenAL32.lib")
#else // WIN64
#pragma comment(lib,"OpenAL64.lin")
#endif

/*
設計はらくだが
処理的にはXAudio2よりやることが多い
サンプリングデプス等をやってくれない

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
		//	// ビットに情報を書き込んでる?????
		//	//ALchar ap;
		//	//ALCchar b;
		//}
	}
}