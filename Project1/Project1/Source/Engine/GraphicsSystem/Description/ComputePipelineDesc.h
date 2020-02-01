#pragma once
#include <d3d12.h>
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRootSignature;
		class IShader;

		struct ComputePipelineDesc
		{
			IRootSignature* rootSignature;			// ���[�g�V�O�l�`��
			IShader* computeShader;					// �R���s���[�g�V�F�[�_�[
			uint32_t nodeMask;
		};

	}
}
