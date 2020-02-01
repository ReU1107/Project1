#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		class ICommandList;

		class ICommandQueue
		{
		public:
			virtual ~ICommandQueue() {};

			virtual void* GetNativeQueue() const = 0;
			// リストの実行が終わるまで待機
			virtual void WaitExecutionList() = 0;

			// リスト配列実行
			virtual void ExecuteLists(ICommandList* lists[], uint32_t listCount) = 0;

		};

	}

}