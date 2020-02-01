#pragma once
#include <cstdint>
#include <dxgiformat.h>
namespace Engine 
{

	namespace GraphicsSystem 
	{
		// ���_�C���f�b�N�X�t�H�[�}�b�g
		enum class IndexFormat : uint8_t
		{
			UInt16,		// 16bit 2byte
			UInt32,		// 32bit 4byte
		};

	}
}