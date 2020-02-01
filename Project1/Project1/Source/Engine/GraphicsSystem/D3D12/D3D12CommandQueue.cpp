#include "D3D12CommandQueue.h"
#include <d3d12.h>
#include "D3D12CommandList.h"
#include <cassert>

namespace Engine
{

	namespace GraphicsSystem
	{
		static const uint32_t MaxExecutableCommandListCount = 20;

		D3D12CommandQueue::D3D12CommandQueue()
			: m_nativeQueue(nullptr)
			, m_fence(nullptr)
			, m_handle(nullptr)
			, m_value(0)
		{

		}

		D3D12CommandQueue::~D3D12CommandQueue()
		{
			m_handle = nullptr;
			m_fence->Release();
			m_nativeQueue->Release();
		}

		void* D3D12CommandQueue::GetNativeQueue() const
		{
			return m_nativeQueue;
		}

		void D3D12CommandQueue::WaitExecutionList()
		{
			auto hr = m_nativeQueue->Signal(m_fence, ++m_value);


			if (FAILED(hr))
			{
				assert(!"シグナル失敗しました");
			}
			//auto v = m_fence->GetCompletedValue();
			//if (v <= m_value)
			{
				hr = m_fence->SetEventOnCompletion(m_value, (HANDLE)m_handle);
				
				if (FAILED(hr))
				{
					assert(!"イベント待機で失敗しました");
				}
				WaitForSingleObject((HANDLE)m_handle, INFINITE);
			}
		}
		
		void D3D12CommandQueue::ExecuteLists(ICommandList* lists[], uint32_t listCount)
		{
			ID3D12CommandList* nativeLists[MaxExecutableCommandListCount] = {};

			for (uint32_t i = 0; i < listCount; ++i)
			{
				lists[i]->Close();
				nativeLists[i] = (ID3D12GraphicsCommandList5*)lists[i]->GetNativeCommandList();
			}
			m_nativeQueue->ExecuteCommandLists(listCount, nativeLists);
		}
	}
}