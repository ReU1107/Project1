#pragma once
//#include "../..//IUnknown.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class IGraphicsPipeline;

		class IContext //: public IUnknown
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~IContext() {}

			virtual void SetPipeline(IGraphicsPipeline* pipeline) = 0;

		};

	}

}