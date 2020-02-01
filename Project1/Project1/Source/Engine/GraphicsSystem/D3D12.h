#pragma once

/*
���񂾂��͂��邳���Ă��炢�܂�
*/
#include <cstdint>
#include <iostream>

/*
����h,cpp�̏����͈ړ����܂�
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
		// �J�n
		void Startup(void* hWnd, uint64_t width, uint64_t height);

		D3D12Device* GetD3D12Device();

		void Present();
		// 
		uint32_t GetCurrentIndex();
		// 
		std::shared_ptr<RenderTexture> GetCurrentBackBuffer();
		std::shared_ptr<DepthTexture> GetDefaultDepthTexture();
		// �I��
		void Shutdown();
	}

}