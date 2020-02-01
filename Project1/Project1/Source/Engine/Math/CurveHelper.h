#pragma once
#include <vector>
namespace Engine
{

	// 前方宣言
	struct Vector2;

	// ベジェ曲線
	// ド・カステリョアルゴリズム(曲線上のinterpolationの点取得)
	inline void DeCasteljauAlgorithm(Vector2& destination, const std::vector<Vector2>& controllPoint, uint32_t controllCount, float interpolation);
	// ベジェ曲線連結
	//inline void Concatenate();

	// 線形補間
	inline float LinearInterpolation(float time, float startTime, float startValue, float endTime, float endValue);

	// イーズインアウト補間
	inline float EaseInOutInterpolation(float time, float startTime, float startValue, float startTangent, float endTime, float endValue, float endTangent);

	// B-スプライン曲線
}


#include "CurveHelperImpl.h"