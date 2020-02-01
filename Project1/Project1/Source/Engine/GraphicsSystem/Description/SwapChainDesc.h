#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class ResourceFormat : uint8_t;
		class IDevice;
		class ICommandQueue;

		struct SwapChainDesc
		{
			void* hWnd;				// �E�B���h�E�n���h��
			ICommandQueue* queue;	// �f�o�C�X
			uint32_t width;			// ��
			uint32_t height;		// ����
			uint32_t count;			// ��
			ResourceFormat format;	// �t�H�[�}�b�g
		};
	}
}