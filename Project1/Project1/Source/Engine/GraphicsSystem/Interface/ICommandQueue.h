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
			// ���X�g�̎��s���I���܂őҋ@
			virtual void WaitExecutionList() = 0;

			// ���X�g�z����s
			virtual void ExecuteLists(ICommandList* lists[], uint32_t listCount) = 0;

		};

	}

}