#include "DDSLoader.h"
#include "../..//../..//Library/DirectXTex/Include/DirectXTex.h"
#include "../..//../..//Library/DirectXTex/Include/DDSTextureLoader12.h"
#include "..///..//../..//Library/DirectXTex/Include/d3dx12.h"
#include "../../String/StringHelper.h"
#include "../D3D12/D3D12Device.h"
#include "../D3D12.h"
#include "../Description/Include.h"
#include "../D3D12/D3D12Resource.h"
#include "../HardwareCommand/CommandList.h"
#include "../HardwareCommand/GraphicsCommandList.h"
#include "../Interface/ICommandList.h"

// ライブラリはソリューションファイルがある場所から探す
#if _DEBUG
#pragma comment(lib,"Library/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib,"Library/DirectXTex/x64/Release/DirectXTex.lib")
#endif

using namespace DirectX;

namespace Engine {
	namespace GraphicsSystem {
		DDSLoader::DDSLoader()
		{

		}

		DDSLoader::~DDSLoader()
		{
			
		}

		IResource* DDSLoader::LoadTexture(const std::string& name)
		{
			const wchar_t* path = ConvertCharToWChar(name.c_str());

			auto device = GraphicsSystem::GetD3D12Device()->GetNativeDevice();
			ID3D12Resource* nativeResource = nullptr;
			std::unique_ptr<uint8_t[]> data;
			std::vector<D3D12_SUBRESOURCE_DATA> subResources;
			if (FAILED(LoadDDSTextureFromFile(device, path, &nativeResource, data, subResources)))
			{
				return nullptr;
			}
			
			auto desc = nativeResource->GetDesc();
			D3D12_PLACED_SUBRESOURCE_FOOTPRINT layouts[100] = {};
			uint32_t rowCounts[100] = {};
			uint64_t rowBytes[100] = {};
			uint32_t subResourceCount = subResources.size();
			uint64_t totalBytes = 0;
			device->GetCopyableFootprints(&desc, 0, subResourceCount, 0, layouts, rowCounts, rowBytes, &totalBytes);

			// コピー元を作成する
			desc = {};
			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Width = totalBytes;
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.SampleDesc.Count = 1;
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			// コピー元にデータを入れる
			D3D12_HEAP_PROPERTIES prop = {};
			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			ID3D12Resource1* copyResource = nullptr;
			if (FAILED(device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&copyResource))))
			{
				assert(!"コピー用のバッファの作成に失敗しました");
			}
			auto commandList = CommandList::Find<GraphicsCommandList>("Graphics");

			ID3D12GraphicsCommandList5* list = (ID3D12GraphicsCommandList5*)commandList->GetInterface()->GetNativeCommandList();

			UpdateSubresources(list, nativeResource, copyResource, 0, 0, subResourceCount, subResources.data());
		
			D3D12_RESOURCE_BARRIER  barrier;
			memset(&barrier, 0, sizeof(barrier));
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Transition.pResource = nativeResource;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;

			list->ResourceBarrier(1, &barrier);

			//copyResource->Release();
			nativeResource->SetName(path);

			D3D12Resource* resource = new D3D12Resource();
			resource->m_nativeResource = (ID3D12Resource1*)nativeResource;

			return resource;
		}
	}

	//void UpdateSubResources(D3D12_SUBRESOURCE_DATA subResources[], 
	//	D3D12_PLACED_SUBRESOURCE_FOOTPRINT layouts[],
	//	uint32_t rowCounts[], uint32_t rowSizeInBytes[],
	//	uint32_t subResourceCount, uint8_t* mapData)
	//{
	//	for (uint32_t i = 0; i < subResourceCount; i++)
	//	{
	//		auto& source = subResources[i];
	//		D3D12_PLACED_SUBRESOURCE_FOOTPRINT& layout = layouts[i];
	//		uint32_t rowCount = rowCounts[i];
	//		uint64_t rowSizeInByte = rowSizeInBytes[i];
	//		uint32_t depth = layout.Footprint.Depth;

	//		D3D12_MEMCPY_DEST dest = { mapData + layout.Offset,layout.Footprint.RowPitch,layout.Footprint.RowPitch * rowCount };

	//		for (uint32_t j = 0; j < depth; ++j)
	//		{
	//			auto destSlice = (uint8_t*)dest.pData + (dest.SlicePitch * j);
	//			auto sourceSlice = (uint8_t*)source.pData + (source.SlicePitch * j);

	//			for (uint32_t k = 0; k < rowCount; ++k)
	//			{
	//				memcpy(destSlice + (dest.RowPitch * k),
	//					sourceSlice + (source.RowPitch * k),
	//					rowSizeInByte);
	//			}

	//		}
	//	}
	//}


	//Object * DDSLoader::Load(const char * filePath)
	//{
	//	const wchar_t * path = ConvertCharToWChar(filePath);

	//	ID3D11Device * device = m_device;

	//	ID3D11Resource * resource = nullptr;
	//	ID3D11ShaderResourceView * shaderResourceView = nullptr;

	//	if (FAILED(DirectX::CreateDDSTextureFromFile(device, path, &resource, &shaderResourceView))) {
	//		MessageBox(nullptr, "DDSファイルの読み込みに失敗しました", filePath, MB_OK);
	//		return nullptr;
	//	}

	//	uint32_t width = 0;
	//	uint32_t height = 0;

	//	D3D11_RESOURCE_DIMENSION dimension;
	//	resource->GetType(&dimension);
	//	if (dimension == D3D11_RESOURCE_DIMENSION_TEXTURE2D) {
	//		//auto tmp = dynamic_cast<ID3D11Texture2D *>(resource);
	//		ID3D11Texture2D * texture = (ID3D11Texture2D*)resource;
	//		D3D11_TEXTURE2D_DESC desc;
	//		texture->GetDesc(&desc);
	//		width = desc.Width;
	//		height = desc.Height;
	//		Texture2D * texture2d = new Texture2D(width, height);
	//		texture2d->m_resource = texture;
	//		texture2d->m_shaderResourceView = shaderResourceView;
	//		return texture2d;
	//	}
	//	else if (dimension == D3D11_RESOURCE_DIMENSION_TEXTURE3D) {
	//		//Texture3D * texture = new Texture3D();
	//		//width = 0;
	//		//height = 0;
	//		//return texture;
	//	}

	//	return nullptr;
	//}

}