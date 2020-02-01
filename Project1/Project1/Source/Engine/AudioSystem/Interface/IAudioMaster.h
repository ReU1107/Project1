#pragma once
#include "IAudioComponent.h"

namespace Engine 
{

	namespace AudioSystem 
	{

		class IAudioMaster : public IAudioComponent
		{
		public:
			// 仮想デストラクタ
			virtual ~IAudioMaster() {}

		};

	}

}