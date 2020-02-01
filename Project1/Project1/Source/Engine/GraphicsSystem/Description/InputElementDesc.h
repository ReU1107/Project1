#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class ResourceFormat : uint8_t;
		enum class InputClassification;

		struct InputElementDesc
		{
			const char* semanticName;				// �Z�}���e�B�N�X��
			uint32_t semanticIndex;					// �Z�}���e�B�N�X�ԍ�(���O����������Ɏg�p�����{�I�ɂ͂O)
			ResourceFormat format;					// �t�H�[�}�b�g
			uint32_t inputSlot;						// 
			uint32_t aligneOffset;					// ��{0xffffffff
			InputClassification classification;		// ����

			uint32_t instanceCount;					// �C���X�^���X�̎��Ɏg�p(����ȊO�̎���0�Œ�)
		};
	}
}