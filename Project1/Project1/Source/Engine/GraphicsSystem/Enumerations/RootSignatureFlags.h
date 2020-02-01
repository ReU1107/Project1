#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		enum class RootSignatureFlags : uint8_t
		{
			None = 0,								// �Ȃ�
			AllowInputAssemblerInputLayout = 0x1,	// �C���v�b�g�A�Z���u��,���C�A�E�g�w���
			DenyVertexShaderRootAccess = 0x2,		// ���_�V�F�[�_�[�ŃA�N�Z�X���Ȃ�
			DenyHullShaderRootAccess = 0x4,			// �n���V�F�[�_�[�ŃA�N�Z�X���Ȃ�
			DenyDomaionShaderRootAccess = 0x8,		// �h���C���V�F�[�_�[�ŃA�N�Z�X���Ȃ�
			DenyGeometryShaderRootAccess = 0x10,	// �W�I���g���V�F�[�_�[�ŃA�N�Z�X���Ȃ�
			DenyPixelShaderRootAccess = 0x20,		// �s�N�Z���V�F�[�_�[�ŃA�N�Z�X���Ȃ�
			AllowStreamOutput = 0x40,				// �X�g���[���A�E�g��w�肩
			LocalRootSignature = 0x80				// ���[�J�����[�g�V�O�l�`���Ƃ��Ďg�p
		};

	}

}