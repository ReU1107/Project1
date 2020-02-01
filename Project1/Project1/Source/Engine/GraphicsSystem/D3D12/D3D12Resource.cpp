#include "D3D12Resource.h"
#include <d3d12.h>
#include <cassert>

namespace Engine 
{

	namespace GraphicsSystem 
	{

		D3D12Resource::D3D12Resource()
			: m_nativeResource(nullptr)
		{
			
		}

		D3D12Resource::~D3D12Resource()
		{
			m_nativeResource->Release();
		}

		void* D3D12Resource::GetNativeResource() const
		{
			return m_nativeResource;
		}

		void D3D12Resource::Update(void* data, uint64_t size, uint64_t begin, uint64_t end)
		{
			uint8_t* mapData = nullptr;
			D3D12_RANGE range = {};
			range.Begin = begin;
			range.End = end;
			auto hr = m_nativeResource->Map(0, &range, (void**)&mapData);
			if (FAILED(hr))
			{
				assert(!"バッファの書き込みに失敗しました");
				ID3D12Device6* device = nullptr;
				m_nativeResource->GetDevice(IID_PPV_ARGS(&device));
				auto hr = device->GetDeviceRemovedReason();
				hr = hr;
			}
			memcpy(mapData, data, size);
			m_nativeResource->Unmap(0, &range);

		}

		uint8_t* D3D12Resource::Map(uint64_t begin, uint64_t end)
		{
			uint8_t* mapData = nullptr;
			D3D12_RANGE range = {};
			range.Begin = begin;
			range.End = end;
			auto hr = m_nativeResource->Map(0, &range, (void**)& mapData);

			return mapData;
		}

		void D3D12Resource::Unmap(uint64_t begin, uint64_t end)
		{
			D3D12_RANGE range = {};
			range.Begin = begin;
			range.End = end;
			m_nativeResource->Unmap(0, &range);
		}

	}
}