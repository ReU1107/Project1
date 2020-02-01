#pragma once
#include "../../Math/Include.h"
#include "../../InstanceID.h"

namespace Engine
{
	namespace AnimationSystem
	{

		/*
		�g�����X�t�H�[�����ꂼ�ꂪ
		�A�j���[�V�������~�܂��������̓A�j���[�V������1����Đ����Ȃ������Ƃ����Ƃ���
		1�xT�|�[�Y(�f�t�H���g)�̃|�[�Y�ɖ߂�Ȃ��ƒl�����������Ȃ邽��
		�̏������p�̒l
		unity�ł�
		classID 137 SkinnedMeshRenderer;
		https://docs.unity3d.com/ja/current/Manual/ClassIDReference.html
		*/

		struct SkeletonBone
		{
			Vector4 rotation;	// ��]
			Vector3 position;	// �ʒu
			Vector3 scale;		// �X�P�[��
			InstanceID id;

			SkeletonBone();
		};
	}
}