#pragma once
#include <cstdint>

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// ���\�[�X�̎g�p���\���݂����Ȃ���
		enum class ResourceFlags : uint8_t
		{
			None = 0x0,						// �Ȃ�
			AllowRenderTarget = 0x01,		// �`���w�苖��
			AllowDepthStencil = 0x02,		// �[�x�A�X�e���V���������݋���
			AllowUnorderedAccess = 0x04,	// �R���s���[�g�V�F�[�_�[�̃A�N�Z�X����
			DenyShaderResource = 0x08,		// �V�F�[�_�[���\�[�X�w��s����
			AllowCrossAdapter = 0x10,		// �ʁX�̃A�_�v�^�[�ł̎g�p����
			AllowSimultaneousAccess = 0x20,	// 
			DecodeReferenceOnly = 0x40,		// 
		};

	}

}