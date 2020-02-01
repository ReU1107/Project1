#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// ���_�̃{�[���e�����
		struct BoneWeight
		{
			uint32_t boneIndex0;	// 1 �߂̃{�[���̃C���f�b�N�X
			uint32_t boneIndex1;	// 2 �߂̃{�[���̃C���f�b�N�X
			uint32_t boneIndex2;	// 3 �߂̃{�[���̃C���f�b�N�X
			uint32_t boneIndex3;	// 4 �߂̃{�[���̃C���f�b�N�X
			float weight0;			// 1 �߂̃{�[���ŃX�L�j���O���Ă���E�F�C�g
			float weight1;			// 2 �߂̃{�[���ŃX�L�j���O���Ă���E�F�C�g
			float weight2;			// 3 �߂̃{�[���ŃX�L�j���O���Ă���E�F�C�g
			float weight3;			// 4 �߂̃{�[���ŃX�L�j���O���Ă���E�F�C�g

			BoneWeight& operator=(const BoneWeight& other)
			{
				this->boneIndex0 = other.boneIndex0;
				this->boneIndex1 = other.boneIndex1;
				this->boneIndex2 = other.boneIndex2;
				this->boneIndex3 = other.boneIndex3;
				this->weight0 = other.weight0;
				this->weight1 = other.weight1;
				this->weight2 = other.weight2;
				this->weight3 = other.weight3;
				return *this;
			}
		};
	}
}