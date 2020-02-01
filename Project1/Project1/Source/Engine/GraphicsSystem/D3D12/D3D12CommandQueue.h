#pragma once
#include "..//Interface/ICommandQueue.h"

struct ID3D12CommandQueue;
struct ID3D12Fence1;

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12CommandQueue : public ICommandQueue
		{
		public:
			ID3D12CommandQueue* m_nativeQueue;	// 
			ID3D12Fence1* m_fence;				// 
			void* m_handle;						// イベントハンドル
			uint64_t m_value;					// イベント制御値
		public:
			// コンストラクタ
			D3D12CommandQueue();
			// デストラクタ
			virtual ~D3D12CommandQueue();

			virtual void* GetNativeQueue() const override;

			// リストの実行が終わるまで待機
			virtual void WaitExecutionList() override;

			// リスト配列実行
			virtual void ExecuteLists(ICommandList* lists[], uint32_t listCount) override;

		};

	}

}

