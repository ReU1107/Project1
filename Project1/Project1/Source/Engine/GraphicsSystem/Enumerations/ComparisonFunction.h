#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// ��r�֐�
		enum class ComparisonFunction : uint8_t
		{
			Never,			// �S�ĕs���i
			Less,			// �������Ȃ獇�i
			Equal,			// �������Ȃ獇�i
			LessEqual,		// �ȉ��Ȃ獇�i
			Greater,		// �傫���Ȃ獇�i
			NotEqual,		// �������Ȃ��Ȃ獇�i
			GreaterEqual,	// �ȏ�Ȃ獇�i
			Always,			// �S�č��i
		};
	}
}