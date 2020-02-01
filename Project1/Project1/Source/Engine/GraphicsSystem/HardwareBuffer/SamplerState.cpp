#include "SamplerState.h"
#include "../D3D12.h"
#include "../D3D12/D3D12Device.h"
#include "ResourceDescriptor.h"
#include "../Interface/IDescriptorHeap.h"
#include "../D3D12/D3D12DescriptorHeap.h"
#include "../D3D12/D3D12Enumeration.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		SamplerState::SamplerState()
		{
			m_desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			m_desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			m_desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			m_desc.BorderColor[0] = 0;
			m_desc.BorderColor[1] = 0;
			m_desc.BorderColor[2] = 0;
			m_desc.BorderColor[3] = 0;

			m_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
			m_desc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			m_desc.MaxAnisotropy = 0;
			m_desc.MaxLOD = 0.0f;
			m_desc.MinLOD = 0.0f;
			m_desc.MipLODBias = 0.0f;

		}

		SamplerState::~SamplerState()
		{

		}

		void SamplerState::CreateSamplerState(ResourceDescriptor* descriptor)
		{
			auto device = GetD3D12Device()->m_device;

			auto heap = (D3D12DescriptorHeap*)descriptor->GetInterface();

			auto type = D3D12DescriptorHeapType(heap->m_type);

			auto* descriptorHeap = heap->m_native;
			D3D12_CPU_DESCRIPTOR_HANDLE handle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();

			// タイプに基づいたサイズ取得
			uint32_t size = device->GetDescriptorHandleIncrementSize(type);
			uint32_t index = heap->m_index++;
			uint64_t stride = (uint64_t)size * index;

			// 作成済みの場所の次から作成する
			handle.ptr += stride;

			device->CreateSampler(&m_desc, handle);

		}

		void SamplerState::CreateSamplerState(IDescriptorHeap* descriptor)
		{
		}
	}
}