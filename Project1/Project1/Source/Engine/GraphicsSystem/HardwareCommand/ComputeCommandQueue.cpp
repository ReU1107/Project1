#include "ComputeCommandQueue.h"
#include "..//D3D12/D3D12Device.h"
#include "..//D3D12.h"
#include "..//Description/CommandQueueDesc.h"
#include "..//Enumerations/CommandListType.h"
#include "ComputeCommandList.h"
#include "../Interface/ICommandQueue.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		ComputeCommandQueue::ComputeCommandQueue()
			: base()
		{
		}

		ComputeCommandQueue::~ComputeCommandQueue()
		{
		}

		ComputeCommandQueue::ComputeCommandQueuePtr ComputeCommandQueue::Create(const std::string& name, CommandQueuePriority priority)
		{
			auto device = GetD3D12Device();

			CommandQueueDesc desc = {};
			desc.type = CommandListType::Compute;
			desc.priority = priority;

			auto queue = std::make_shared<ComputeCommandQueue>();
			queue->m_interface = device->CreateCommandQueue(desc);
			queue->SetName(name);

			Register(name, queue);
			return queue;
		}

		void ComputeCommandQueue::ExecuteCommandLists(ComputeCommandListPtr lists[], uint32_t count)
		{
			ICommandList* nativeLists[20] = {};
			for (uint32_t i = 0; i < count; ++i)
			{
				nativeLists[i] = lists[i]->GetInterface();
			}
			m_interface->ExecuteLists(nativeLists, count);
		}
	}
}