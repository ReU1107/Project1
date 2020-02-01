#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		struct InputElementDesc;

		struct InputLayoutDesc
		{
			InputElementDesc* elements;	// �G�������g�z��
			uint32_t elementCount;	// �G�������g��
		};
	}
}