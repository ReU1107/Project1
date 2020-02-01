#pragma once
#include "CommandQueue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class CopyCommandList;
		class CopyCommandQueue : public CommandQueue
		{
		private:
			using base = CommandQueue;
			using CopyCommandQueuePtr = std::shared_ptr<CopyCommandQueue>;
			using CopyCommandListPtr = std::shared_ptr<CopyCommandList>;

		public:
			// �R�}���h���X�g
			CopyCommandQueue();
			// �f�X�g���N�^
			virtual ~CopyCommandQueue();

			static CopyCommandQueuePtr Create(const std::string& name, CommandQueuePriority priority = CommandQueuePriority::Normal);
		public:
			// �R�}���h���X�g���s
			void ExecuteCommandLists(CopyCommandListPtr lists[], uint32_t count);
		};
	}
}