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
			// 仮想デストラクタ
			virtual ~IContext() {}

			virtual void SetPipeline(IGraphicsPipeline* pipeline) = 0;

		};

	}

}