#pragma once
#include <cstdint>

/*
ShaderResouce�̒萔�o�b�t�@���
*/
/*
D3D12_ROOT_CONSTANTS
*/

namespace Engine
{

	namespace GraphicsSystem
	{
		// size���w�肵���萔��z�u����
		struct ShaderResourceConstantsDesc
		{
			uint32_t size;			// �傫��
			uint32_t index;			// �ꏊ
			uint32_t space;			// ���
		};
	}

}