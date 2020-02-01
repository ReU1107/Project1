#pragma once
#include "../Interface/IAccelerationStructure.h"
#include <d3d12.h>
#include <vector>

namespace Engine
{
	namespace GraphicsSystem
	{
		class D3D12AccelerationStructure : public IAccelerationStructure
		{
		public:

			ID3D12Resource1* m_scratch;			// 作成時に必要
			ID3D12Resource1* m_result;			// toplevelに登録する際に必要
			ID3D12Resource1* m_update;			// 更新をする際に必要

		public:
			// 
			D3D12AccelerationStructure();
			// 
			virtual ~D3D12AccelerationStructure();

			// 
			virtual void* GetNativeResource() const override;

			// 更新
			virtual void Update(void* data, uint64_t size, uint64_t begin = 0, uint64_t end = 0) override {}

			// 外部で書き込みをさせる際に使用(呼出し後は必ずUnmapを読んでください)
			virtual uint8_t* Map(uint64_t begin = 0, uint64_t end = 0) override { return nullptr; }

			// 外部で書き込みをさせる際に使用(Map後に必ず読んでください)
			virtual void Unmap(uint64_t begin = 0, uint64_t end = 0) override {}
		};
	}
}