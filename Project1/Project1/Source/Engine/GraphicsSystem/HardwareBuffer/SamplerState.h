#pragma once
#include <d3d12.h>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IDescriptorHeap;
		class ResourceDescriptor;

		class SamplerState
		{
		private:
			D3D12_SAMPLER_DESC m_desc;
			
		public:
			// コンストラクタ
			SamplerState();
			// デストラクタ
			~SamplerState();

			void CreateSamplerState(ResourceDescriptor* descriptor);
			void CreateSamplerState(IDescriptorHeap* descriptor);
		};

	}

}