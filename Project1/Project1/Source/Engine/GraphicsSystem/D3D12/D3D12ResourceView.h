#pragma once
#include "..//Interface/IResourceView.h"
#include <d3d12.h>
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12ResourceView : public IResourceView
		{
		public:
			D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;	// cpuハンドル
			D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;	// gpuハンドル
			uint32_t m_index;							// 
			bool m_isCopy;								// 別のデスクリプターヒープにコピーされた(後で問題が起こるかも)
			// 問題の詳細　パイプラインが単一のデスクリプターを持っているためそれぞれのパイプラインで使用するときにコピーするから
		public:
			// コンストラクタ
			D3D12ResourceView();
			// デストラクタ
			virtual ~D3D12ResourceView();

		};


	}

}