#pragma once
#include "..//Interface/IResource.h"

// �O���錾
struct ID3D12Resource1;

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12Resource final : public IResource
		{
		public:
			ID3D12Resource1* m_nativeResource;	// �l�C�e�B�u���\�[�X

		public:
			// �R���X�g���N�^
			D3D12Resource();
			// �f�X�g���N�^
			virtual ~D3D12Resource();
			// 
			virtual void* GetNativeResource() const override;
			// 
			virtual void Update(void* data, uint64_t size, uint64_t begin = 0, uint64_t end = 0) override;
			// 
			virtual uint8_t* Map(uint64_t begin = 0, uint64_t end = 0) override;
			// 
			virtual void Unmap(uint64_t begin = 0, uint64_t end = 0) override;

		};

	}

}