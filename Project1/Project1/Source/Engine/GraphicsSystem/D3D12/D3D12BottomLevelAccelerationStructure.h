#pragma once
#include "D3D12AccelerationStructure.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class D3D12BottomLevelAccelerationStructure : public D3D12AccelerationStructure
		{
		public:
			std::vector<D3D12_RAYTRACING_GEOMETRY_DESC> m_nativeDescs;	// 
			D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS m_flags;	// 

		public:
			// �R���X�g���N�^
			D3D12BottomLevelAccelerationStructure();
			// �f�X�g���N�^
			virtual ~D3D12BottomLevelAccelerationStructure();

			virtual void Update(const TopLevelAccelerationStructureDesc& desc) override;

		};

		using D3D12BottomLevelAS = D3D12BottomLevelAccelerationStructure;
	}
}