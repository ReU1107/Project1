#pragma once
#include "../Interface/IComputePipeline.h"

struct ID3D12PipelineState;

namespace Engine
{
	namespace GraphicsSystem
	{

		class D3D12ComputePipeline : public IComputePipeline
		{
		public:
			ID3D12PipelineState* m_native;
		public:
			// コンストラクタ
			D3D12ComputePipeline();
			// デストラクタ
			virtual ~D3D12ComputePipeline();
		public:
			virtual void* GetNativePipeline() const override;

		};
	}
}