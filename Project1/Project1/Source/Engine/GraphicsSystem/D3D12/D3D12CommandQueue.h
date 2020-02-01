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
			void* m_handle;						// �C�x���g�n���h��
			uint64_t m_value;					// �C�x���g����l
		public:
			// �R���X�g���N�^
			D3D12CommandQueue();
			// �f�X�g���N�^
			virtual ~D3D12CommandQueue();

			virtual void* GetNativeQueue() const override;

			// ���X�g�̎��s���I���܂őҋ@
			virtual void WaitExecutionList() override;

			// ���X�g�z����s
			virtual void ExecuteLists(ICommandList* lists[], uint32_t listCount) override;

		};

	}

}

