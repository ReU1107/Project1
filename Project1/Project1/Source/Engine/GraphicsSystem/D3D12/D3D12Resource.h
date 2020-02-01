#pragma once
#include "..//Interface/IResource.h"

// 前方宣言
struct ID3D12Resource1;

namespace Engine 
{

	namespace GraphicsSystem 
	{

		class D3D12Resource final : public IResource
		{
		public:
			ID3D12Resource1* m_nativeResource;	// ネイティブリソース

		public:
			// コンストラクタ
			D3D12Resource();
			// デストラクタ
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