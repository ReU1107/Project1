#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class BufferType : uint8_t
		{
			Vertex,		// ���_
			Index,		// �C���f�b�N�X
			Constant,	// �萔
			Structure,	// �\����
		};
	}
}