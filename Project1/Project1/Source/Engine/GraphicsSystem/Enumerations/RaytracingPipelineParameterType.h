#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem 
	{
		// ���C�g���[�V���O�T�u�X�e�[�g
		enum class RaytracingPipelineParameterType : uint8_t
		{
			PipelineConfig,	// �p�C�v���C���R���t�B�O
			ShaderConfig,	// �V�F�[�_�[�R���t�B�O
			Association,	// �A�\�V�G�[�V����
			ShaderLibrary,	// �V�F�[�_�[���C�u�����[
			Signature,		// �V�O�l�`��
			HitGroup,		// �q�b�g�O���[�v
		};
	}
}