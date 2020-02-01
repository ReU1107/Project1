#include "CommandQueue.h"
#include "CommandList.h"
#include "..//Interface/ICommandQueue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		CommandQueue::CommandQueue()
			: base("コマンドキュー")
			, m_interface(nullptr)
		{
		}

		CommandQueue::~CommandQueue()
		{
			delete m_interface;
		}

		ICommandQueue* CommandQueue::GetInterface() const
		{
			return m_interface;
		}

		void CommandQueue::WaitExecutionList()
		{
			m_interface->WaitExecutionList();
		}
	}
}