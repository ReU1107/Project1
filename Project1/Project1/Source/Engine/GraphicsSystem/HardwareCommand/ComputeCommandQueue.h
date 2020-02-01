#pragma once
#include "CommandQueue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class ComputeCommandList;
		class ComputeCommandQueue : public CommandQueue
		{
		private:
			using base = CommandQueue;
			using ComputeCommandQueuePtr = std::shared_ptr<ComputeCommandQueue>;
			using ComputeCommandListPtr = std::shared_ptr<ComputeCommandList>;

		public:
			// �R�}���h���X�g
			ComputeCommandQueue();
			// �f�X�g���N�^
			virtual ~ComputeCommandQueue();

			static ComputeCommandQueuePtr Create(const std::string& name, CommandQueuePriority priority = CommandQueuePriority::Normal);
		public:
			// �R�}���h���X�g���s
			void ExecuteCommandLists(ComputeCommandListPtr lists[], uint32_t count);
		};
	}
}