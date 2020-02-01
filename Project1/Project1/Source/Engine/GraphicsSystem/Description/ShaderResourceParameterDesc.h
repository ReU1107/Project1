#pragma once
#include <cstdint>

/*
D3D12_DESCRIPTOR_RANGE
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class ShaderResourceType : uint8_t;

		struct ShaderResourceParameterDesc
		{
			uint32_t index;				// �z�u����ꏊ
			uint32_t count;				// �z�u���鐔
			uint32_t space;				// �z�u������
			ShaderResourceType type;	// �z�u���郊�\�[�X�̎��
		};
	}

}