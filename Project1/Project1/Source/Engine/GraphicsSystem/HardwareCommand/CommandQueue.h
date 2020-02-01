#pragma once
#include "..//Enumerations/CommandQueuePriority.h"
#include "../../Utility/AccessObject.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class ICommandQueue;
		class ICommandList;
		class CommandList;

		class CommandQueue : public AccessObject<CommandQueue>
		{
		private:
			using base = AccessObject<CommandQueue>;
		protected:
			ICommandQueue* m_interface;
		
		public:
			// �R�}���h���X�g
			CommandQueue();
			// �f�X�g���N�^
			virtual ~CommandQueue();

			ICommandQueue* GetInterface() const;

			void WaitExecutionList();

		};
	}
}