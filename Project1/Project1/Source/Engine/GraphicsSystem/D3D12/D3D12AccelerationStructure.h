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

			ID3D12Resource1* m_scratch;			// �쐬���ɕK�v
			ID3D12Resource1* m_result;			// toplevel�ɓo�^����ۂɕK�v
			ID3D12Resource1* m_update;			// �X�V������ۂɕK�v

		public:
			// 
			D3D12AccelerationStructure();
			// 
			virtual ~D3D12AccelerationStructure();

			// 
			virtual void* GetNativeResource() const override;

			// �X�V
			virtual void Update(void* data, uint64_t size, uint64_t begin = 0, uint64_t end = 0) override {}

			// �O���ŏ������݂�������ۂɎg�p(�ďo����͕K��Unmap��ǂ�ł�������)
			virtual uint8_t* Map(uint64_t begin = 0, uint64_t end = 0) override { return nullptr; }

			// �O���ŏ������݂�������ۂɎg�p(Map��ɕK���ǂ�ł�������)
			virtual void Unmap(uint64_t begin = 0, uint64_t end = 0) override {}
		};
	}
}