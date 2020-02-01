#include "TGALoader.h"
#include "../..//..//../Library/DirectXTex/Include/DirectXTex.h"
#include "../../String/StringHelper.h"
#include "../D3D12.h"
#include "..//D3D12/D3D12Device.h"
#include "../D3D12/D3D12Resource.h"
#include "../Description/Include.h"
#include "../Enumerations/Include.h"
#include <cassert>
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
namespace Engine
{
	namespace GraphicsSystem
	{
		TGALoader::TGALoader()
		{
		}

		TGALoader::~TGALoader()
		{
		}

		IResource* GraphicsSystem::TGALoader::LoadTexture(const std::string& fileName)
		{
			const wchar_t* path = ConvertCharToWChar(fileName.c_str());
			DirectX::TexMetadata metaData;
			DirectX::ScratchImage scratchImage;

			if (FAILED(DirectX::LoadFromTGAFile(path, &metaData, scratchImage))) 
			{
				char str[MAX_PATH];
				sprintf_s(str, "TGAファイルの読み込みに失敗しました\n%s", fileName.c_str());
				MessageBox(nullptr, str, "エラー", MB_OK);
				return nullptr;
			}
			auto device = GetD3D12Device()->m_device;

			auto Dimension = [](DirectX::TEX_DIMENSION dimension)->D3D12_RESOURCE_DIMENSION
			{
				switch (dimension)
				{
				case DirectX::TEX_DIMENSION_TEXTURE1D:
					return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
					break;
				case DirectX::TEX_DIMENSION_TEXTURE2D:
					return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
					break;
				case DirectX::TEX_DIMENSION_TEXTURE3D:
					return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
					break;
				default:
					break;
				}

				return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			};

			ID3D12Resource1* nativeResource = nullptr;
			
			D3D12_RESOURCE_DESC desc = {};
			desc.Dimension = Dimension(metaData.dimension);
			desc.Width = (UINT)metaData.width;
			desc.Height = (UINT)metaData.height;
			desc.DepthOrArraySize = (UINT)metaData.arraySize;
			desc.MipLevels = (UINT)metaData.mipLevels;
			desc.Format = metaData.format;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;
			desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			
			D3D12_HEAP_PROPERTIES prop = {};
			prop.Type = D3D12_HEAP_TYPE_DEFAULT;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 1;
			prop.VisibleNodeMask = 1;

			if (FAILED(device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&nativeResource))))
			{
				assert(!"テクスチャの作成に失敗しました");
				return nullptr;
			}

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
			uint64_t totalBytes = 0;
			uint32_t rowCount = 0;
			uint64_t byte = 0;
			device->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &rowCount, &byte, &totalBytes);

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
			prop = {};
			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			ID3D12Resource1* copyResource = nullptr;
			if (FAILED(device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&copyResource))))
			{
				assert(!"コピー用のバッファの作成に失敗しました");
			}

			uint8_t* mapData = nullptr;
			if (FAILED(copyResource->Map(0, nullptr, (void**)& mapData)))
			{
				assert(!"コピー用のマップに失敗しました");
			}
		
			auto images = scratchImage.GetImages();
			uint32_t imageCount = scratchImage.GetImageCount();
			for (uint32_t i = 0; i < imageCount; ++i)
			{
				auto& image = images[i];
				for (uint32_t j = 0; j < rowCount; ++j)
				{
					auto destination = mapData + footprint.Offset + (footprint.Footprint.RowPitch * j);
					auto source = image.pixels + (image.rowPitch * j);
					memcpy(destination, source, image.rowPitch);
				}
			}

			copyResource->Unmap(0, nullptr);
			// VRAMにアクセスしコピー元のデータを送る
			D3D12_TEXTURE_COPY_LOCATION destination = {};
			destination.pResource = nativeResource;
			destination.SubresourceIndex = 0;
			destination.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;

			D3D12_TEXTURE_COPY_LOCATION source = {};
			source.pResource = copyResource;
			source.PlacedFootprint = footprint;
			source.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;

			auto commandList = CommandList::Find<GraphicsCommandList>("Graphics");

			ID3D12GraphicsCommandList5* list = (ID3D12GraphicsCommandList5*)commandList->GetInterface()->GetNativeCommandList();
			list->CopyTextureRegion(&destination, 0, 0, 0, &source, nullptr);

			// コピーコマンドリストではリソースバリアができない
			D3D12_RESOURCE_BARRIER  barrier;
			memset(&barrier, 0, sizeof(barrier));
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Transition.pResource = nativeResource;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;

			list->ResourceBarrier(1, &barrier);

			//copyResource->Release();

			nativeResource->SetName(path);

			D3D12Resource* resource = new D3D12Resource();
			resource->m_nativeResource = (ID3D12Resource1*)nativeResource;

			return resource;
		}

	}

	//Object * TGALoader::Load(const char * filePath)
	//{
	//	

	//	// シェーダーリソースビュー作成
	//	ID3D11ShaderResourceView * shaderResourceView = nullptr;
	//	if (FAILED(DirectX::CreateShaderResourceView(device, scratchImage.GetImages(), scratchImage.GetImageCount(), metaData, &shaderResourceView))) {
	//		MessageBox(nullptr, "シェーダーリソースビューの作成に失敗しました", filePath, MB_OK);
	//		return nullptr;
	//	}

	//	uint32_t width = 0;
	//	uint32_t height = 0;

	//	TEX_DIMENSION dimension = metaData.dimension;
	//	if (dimension == D3D11_RESOURCE_DIMENSION_TEXTURE2D) {
	//		width = metaData.width;
	//		height = metaData.height;

	//		ID3D11Resource * resource = nullptr;
	//		shaderResourceView->GetResource(&resource);
	//		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	//		shaderResourceView->GetDesc(&desc);
	//		Texture2D * texture2d = new Texture2D(width, height);
	//		texture2d->m_resource = resource;
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