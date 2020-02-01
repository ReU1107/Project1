#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class ShaderRecordType : uint8_t
		{
			RayGenerate,	// ���C����
			HitGroup,		// �q�b�g�O���[�v
			Miss,			// �~�X
			Callable,		// 
		};

	}

}