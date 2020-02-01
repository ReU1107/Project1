#pragma once
#include "RenderTargetBlendDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		struct BlendDesc
		{
			bool alphaToCoverageEnable = false;		// �A���t�@�g�D�J�o���b�W
			bool independentBlendEnable = false;	// �����_�[�^�[�Q�b�g���ɐ؂�ւ��邩
			RenderTargetBlendDesc renderTargets[8];	// �����_�[�^�[�Q�b�g

			static BlendDesc NoBlend();
		};
	}
}