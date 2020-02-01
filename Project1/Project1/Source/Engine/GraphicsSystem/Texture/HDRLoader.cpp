#include "HDRLoader.h"
#include "../../..//../Library/DirectXTex/Include/DirectXTex.h"
#include "../../String/StringHelper.h"
#include "Texture.h"

// ライブラリはソリューションファイルがある場所から探す
#if _WIN64
#if _DEBUG
#pragma comment(lib,"Library/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib,"Library/DirectXTex/x64/Release/DirectXTex.lib")
#endif
#else
#if _DEBUG
#pragma comment(lib,"Library/DirectXTex/x86/Debug/DirectXTex.lib")
#else
#pragma comment(lib,"Library/DirectXTex/x86/Release/DirectXTex.lib")
#endif

#endif

using namespace DirectX;
namespace Engine {

	HDRLoader::HDRLoader()
	{
	}

	HDRLoader::~HDRLoader()
	{
	}

	//Object * HDRLoader::Load(const char * filePath)
	//{
	//	const wchar_t * path = ConvertCharToWChar(filePath);

	//	ID3D11Device * device = m_device;
	//	DirectX::TexMetadata metaData;
	//	DirectX::ScratchImage scratchImage;

	//	if (FAILED(DirectX::LoadFromHDRFile(path, &metaData, scratchImage))) {
	//		MessageBox(nullptr, "HDRファイルの読み込みに失敗しました", filePath, MB_OK);
	//		return nullptr;
	//	}

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