#pragma once
#include <cstdint>
#include "../../Math/Include.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		// �u�����h����`��̍����l
		struct BlendShapeDeltaPosition
		{
			uint32_t index;	// �ύX���钸�_�ԍ�
			Vector3 value;	// �����ʒu
		};

		// �u�����h����`��̍����l
		struct BlendShapeDeltaNormal
		{
			uint32_t index;	// �ύX���钸�_�ԍ�
			Vector3 value;	// �����@��
		};

		// �u�����h����`��̍����l
		struct BlendShapeDeltaTangent
		{
			uint32_t index;	// �ύX���钸�_�ԍ�
			Vector4 value;	// �����ڐ�
		};

	}
}