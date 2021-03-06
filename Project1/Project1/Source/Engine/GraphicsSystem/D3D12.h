#pragma once

/*
今回だけはずるさせてもらいます
*/
#include <cstdint>
#include <iostream>

/*
このh,cppの処理は移動します
*/

namespace Engine 
{

	namespace GraphicsSystem
	{
		class D3D12Device;
		class Resource;
		class ResourceView;
		class Texture;
		class RenderTexture;
		class DepthTexture;
		// 開始
		void Startup(void* hWnd, uint64_t width, uint64_t height);

		D3D12Device* GetD3D12Device();

		void Present();
		// 
		uint32_t GetCurrentIndex();
		// 
		std::shared_ptr<RenderTexture> GetCurrentBackBuffer();
		std::shared_ptr<DepthTexture> GetDefaultDepthTexture();
		// 終了
		void Shutdown();
	}

}