#pragma once
#include "IAudioComponent.h"

/*
サブミキシング用

*/
namespace Engine 
{

	namespace AudioSystem 
	{

		class IAudioSubMixer : public IAudioComponent
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioSubMixer() {}

		};

	}

}