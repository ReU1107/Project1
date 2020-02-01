#pragma once
#include <vector>
namespace Engine
{

	// �O���錾
	struct Vector2;

	// �x�W�F�Ȑ�
	// �h�E�J�X�e�����A���S���Y��(�Ȑ����interpolation�̓_�擾)
	inline void DeCasteljauAlgorithm(Vector2& destination, const std::vector<Vector2>& controllPoint, uint32_t controllCount, float interpolation);
	// �x�W�F�Ȑ��A��
	//inline void Concatenate();

	// ���`���
	inline float LinearInterpolation(float time, float startTime, float startValue, float endTime, float endValue);

	// �C�[�Y�C���A�E�g���
	inline float EaseInOutInterpolation(float time, float startTime, float startValue, float startTangent, float endTime, float endValue, float endTangent);

	// B-�X�v���C���Ȑ�
}


#include "CurveHelperImpl.h"