#pragma once
#include "../Interface/IDescriptorHeap.h"
#include <cstdint>
#include <d3d12.h>
struct ID3D12DescriptorHeap;

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12DescriptorHeap : public IDescriptorHeap
		{
		public:
			ID3D12DescriptorHeap* m_native;		// 
			uint32_t m_count;					// 何個分確保したか
			uint32_t m_index;					// 何番目の
			DescriptorHeapType m_type;			// 何用のヒープか
		public:
			// コンストラクタ
			D3D12DescriptorHeap();
			// デストラクタ
			virtual ~D3D12DescriptorHeap();

			virtual void* GetNativeHeap() const override { return m_native; }

			virtual void Reset(uint32_t index) override;

			D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle() const;

			D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const;

			uint32_t GetCount() const { return m_count; }

			uint32_t GetIndex() const { return m_index; }

			uint32_t operator++()
			{
				return m_index++;
			}

			virtual DescriptorHeapType GetType() const override { return m_type; }
		};
	}
}