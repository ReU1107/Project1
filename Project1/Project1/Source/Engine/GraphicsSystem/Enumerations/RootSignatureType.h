#pragma once
#include <cstdint>

/*
���[�g�V�O�l�`�������X�^���C�Y�@�Ŏg�p����Ȃ�
�K���O���[�o���ɂ���K�v������
���C�g���[�V���O�@�Ȃ�
�����g���\��������
*/

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// ���[�g�V�O�l�`�������C�g���[�V���O�̂ǂ���Ƃ��Ďg�p���邩
		enum class RootSignatureType : uint8_t
		{
			Global,	// �O���[�o��
			Local,	// ���[�J��
		};
	}
}
