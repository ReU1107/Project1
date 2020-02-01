#pragma once
#include <cstdint>

namespace Engine 
{
	
	enum class DepthTextureMode : uint8_t
	{
		None,			// �[�x�e�N�X�`���𐶐����Ȃ�
		Depth,			// �[�x�l�̂ݐ���
		DepthNormals,	// �[�x,�@������
		MotionVectors	// ���[�V�����x�N�^�[�쐬
	};

}