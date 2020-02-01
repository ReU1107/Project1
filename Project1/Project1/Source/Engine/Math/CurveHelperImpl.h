#pragma once
#include "CurveHelper.h"

namespace Engine
{

	float LinearInterpolation(float time, float startTime, float startValue, float endTime, float endValue)
	{
		// タイムのウエイト
		float weight = ((time - startTime) / (endTime - startTime));

		float value = ((endValue - startValue) * weight) + startValue;

		return value;
	}

	inline float EaseInOutInterpolation(float time, float startTime, float startValue, float startTangent, float endTime, float endValue, float endTangent)
	{
		// 時間に対しての前のアニメーションの重み
		float prevWeight = (time - startTime) / (endTime - startTime);
		// 後ろのアニメーションの重み
		float followWeight = 1.0f - prevWeight;

		// イーズインアウトの計算式
		float prev = (powf(followWeight, 3.0f) + (3.0f * powf(followWeight, 2.0f) * prevWeight)) * startValue;
		float follow = ((3.0f * powf(prevWeight, 2.0f) * followWeight) + powf(prevWeight, 3.0f)) * endValue;

		// 前後の値の合計
		return prev + follow;
	}
}