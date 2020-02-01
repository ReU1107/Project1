#pragma once
#include "D3D12AccelerationStructure.h"

namespace Engine
{
	namespace GraphicsSystem
	{

		class D3D12TopLevelAccelerationStructure : public D3D12AccelerationStructure
		{
		private:
			using base = D3D12AccelerationStructure;
		public:
			ID3D12Resource1* m_instanceBuffer;
			D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC m_desc;

		public:
			// 
			D3D12TopLevelAccelerationStructure();
			// 
			virtual ~D3D12TopLevelAccelerationStructure();
			// 
			virtual void Update(const TopLevelAccelerationStructureDesc& desc) override;

		};

	}

}