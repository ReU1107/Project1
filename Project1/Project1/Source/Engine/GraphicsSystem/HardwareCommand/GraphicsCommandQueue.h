#pragma once
#include "CommandQueue.h"
#include <string>
#include <unordered_map>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class GraphicsCommandList;

		class GraphicsCommandQueue : public CommandQueue
		{
		private:
			using base = CommandQueue;
			using GraphicsCommandQueuePtr = std::shared_ptr<GraphicsCommandQueue>;
			using GraphicsCommandListPtr = std::shared_ptr<GraphicsCommandList>;
		public:
			// �R�}���h���X�g
			GraphicsCommandQueue();
			// �f�X�g���N�^
			virtual ~GraphicsCommandQueue();

			static GraphicsCommandQueuePtr Create(const std::string& name, CommandQueuePriority priority = CommandQueuePriority::Normal);


		public:
			// �R�}���h���X�g���s
			void ExecuteCommandLists(GraphicsCommandListPtr lists[], uint32_t count);
		};
	}
}