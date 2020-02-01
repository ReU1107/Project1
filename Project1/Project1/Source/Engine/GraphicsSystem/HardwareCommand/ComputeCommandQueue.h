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
			// コマンドリスト
			ComputeCommandQueue();
			// デストラクタ
			virtual ~ComputeCommandQueue();

			static ComputeCommandQueuePtr Create(const std::string& name, CommandQueuePriority priority = CommandQueuePriority::Normal);
		public:
			// コマンドリスト実行
			void ExecuteCommandLists(ComputeCommandListPtr lists[], uint32_t count);
		};
	}
}