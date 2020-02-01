#pragma once

/*
¡‰ñ‚¾‚¯‚Í‚¸‚é‚³‚¹‚Ä‚à‚ç‚¢‚Ü‚·
*/
#include <cstdint>
#include <iostream>

/*
‚±‚Ìh,cpp‚Ìˆ—‚ÍˆÚ“®‚µ‚Ü‚·
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
		// ŠJn
		void Startup(void* hWnd, uint64_t width, uint64_t height);

		D3D12Device* GetD3D12Device();

		void Present();
		// 
		uint32_t GetCurrentIndex();
		// 
		std::shared_ptr<RenderTexture> GetCurrentBackBuffer();
		std::shared_ptr<DepthTexture> GetDefaultDepthTexture();
		// I—¹
		void Shutdown();
	}

}