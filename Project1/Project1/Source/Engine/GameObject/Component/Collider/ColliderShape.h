#pragma once
#include <cstdint>

namespace Engine
{

	/*
	�R���C�_�[�̌`��ɂ���ē����蔻��̂������ς��
	*/

	// �R���C�_�[�̌`��
	enum class ColliderShape : uint8_t
	{
		Box,		// ��
		Capsule,	// �J�v�Z��
		Sphere,		// ��
		Mesh,		// ���b�V��
		Terrain		// �n�`
	};

}