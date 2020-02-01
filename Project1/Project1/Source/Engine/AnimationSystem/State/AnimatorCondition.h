#pragma once
#include "../Enumerations/AnimatorConditionMode.h"

/*
�|�C���^�[�̈�������
��������̌^�̃|�C���^�[�ɃL���X�g���Ă���
���̉�������K�v������
���R:
void * �͎��̉��ł��Ȃ�����
*/

namespace Engine
{

	namespace AnimationSystem
	{

		struct AnimatorCondition
		{
			void* parameter;			// �p�����[�^�[
			float threshold;			// �������l(��r�Ώ�)
			AnimatorConditionMode mode;	// ��r���@

			AnimatorCondition(void* parameter, AnimatorConditionMode mode, float threshold);

			// ��r����
			bool Compare();
		};
	}
}

