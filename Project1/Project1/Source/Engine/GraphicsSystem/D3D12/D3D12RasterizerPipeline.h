#pragma once
#include "..//Interface/IRasterizerPipeline.h"

struct ID3D12PipelineState;

namespace Engine
{
	namespace  GraphicsSystem
	{
		class D3D12RasterizerPipeline : public IRasterizerPipeline
		{
		public:
			ID3D12PipelineState* m_native;
		public:
			// コンストラクタ
			D3D12RasterizerPipeline();
			// デストラクタ
			virtual ~D3D12RasterizerPipeline();

			virtual void* GetNativePipeline() const override;
		};
	}

}