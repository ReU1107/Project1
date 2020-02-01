#pragma once
#include <cstdint>

/*
D3D12_ROOT_DESCRIPTOR
*/
namespace Engine 
{

	namespace GraphicsSystem
	{
		enum class ShaderResourceType : uint8_t;
		/*
		type��sampler���w�肵�Ȃ��ł�������
		*/
		// �ʒu�A��ԂɃ^�C�v�̃��\�[�X��������z�u����
		struct ShaderResourceDescriptorDesc
		{
			uint32_t index;			// �z�u����ʒu
			uint32_t space;			// �z�u������
			ShaderResourceType type;	// �^�C�v
		};
	}

}