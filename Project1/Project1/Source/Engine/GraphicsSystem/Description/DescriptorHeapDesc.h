#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class DescriptorHeapType : uint8_t;

		struct DescriptorHeapDesc
		{
			uint32_t count;				// �쐬�\��̐�
			uint32_t nodeMask;			// 
			DescriptorHeapType type;	// 
			bool shaderAccess;			// �V�F�[�_�[����A�N�Z�X���邩
		};
	}
}