#pragma once
#include "CurveHelper.h"

namespace Engine
{

	float LinearInterpolation(float time, float startTime, float startValue, float endTime, float endValue)
	{
		// �^�C���̃E�G�C�g
		float weight = ((time - startTime) / (endTime - startTime));

		float value = ((endValue - startValue) * weight) + startValue;

		return value;
	}

	inline float EaseInOutInterpolation(float time, float startTime, float startValue, float startTangent, float endTime, float endValue, float endTangent)
	{
		// ���Ԃɑ΂��Ă̑O�̃A�j���[�V�����̏d��
		float prevWeight = (time - startTime) / (endTime - startTime);
		// ���̃A�j���[�V�����̏d��
		float followWeight = 1.0f - prevWeight;

		// �C�[�Y�C���A�E�g�̌v�Z��
		float prev = (powf(followWeight, 3.0f) + (3.0f * powf(followWeight, 2.0f) * prevWeight)) * startValue;
		float follow = ((3.0f * powf(prevWeight, 2.0f) * followWeight) + powf(prevWeight, 3.0f)) * endValue;

		// �O��̒l�̍��v
		return prev + follow;
	}
}