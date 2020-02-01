#include "D3D12TopLevelAccelerationStructure.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include "../D3D12/D3D12Enumeration.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace Engine
{
	namespace GraphicsSystem
	{
		
		D3D12TopLevelAccelerationStructure::D3D12TopLevelAccelerationStructure()
			: base()
			, m_instanceBuffer(nullptr)
			, m_desc()
		{
		}
		
		D3D12TopLevelAccelerationStructure::~D3D12TopLevelAccelerationStructure()
		{
		}

		void D3D12TopLevelAccelerationStructure::Update(const TopLevelAccelerationStructureDesc& desc)
		{
			uint32_t instanceCount = desc.bottomCount;
			D3D12_RAYTRACING_INSTANCE_DESC* instanceDescs = nullptr;
			auto hr = m_instanceBuffer->Map(0, nullptr, (void**)&instanceDescs);
			if (FAILED(hr))
			{
				assert(!"インスタンスへのアクセスに失敗しました");
			}
			memset(instanceDescs, 0, sizeof(D3D12_RAYTRACING_INSTANCE_DESC) * instanceCount);

			for (uint32_t i = 0; i < instanceCount; ++i)
			{
				auto& base = desc.descs[i];
				instanceDescs[i].InstanceID = base.id;
				instanceDescs[i].InstanceContributionToHitGroupIndex = base.contribution;
				instanceDescs[i].Flags = D3D12RaytracingInstanceFlags(base.flags);

				// 変換行列を3x4に変換、設定する
				DirectX::XMFLOAT3X4 m;
				XMStoreFloat3x4(&m, XMLoadFloat4x4(&base.matrix));
				auto transform = instanceDescs[i].Transform;
				for (uint32_t j = 0; j < 3; ++j)
				{
					for (uint32_t k = 0; k < 4; ++k)
					{
						transform[j][k] = m.m[j][k];
					}
				}
				ID3D12Resource1* bottom = (ID3D12Resource1*)base.bottom->GetNativeResource();
				instanceDescs[i].AccelerationStructure = bottom->GetGPUVirtualAddress();
				instanceDescs[i].InstanceMask = base.mask;
			}

			// Unmap
			m_instanceBuffer->Unmap(0, nullptr);
		}
	}
}
