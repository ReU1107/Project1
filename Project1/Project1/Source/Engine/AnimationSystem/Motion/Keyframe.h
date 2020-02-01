#pragma once
#include "../Enumerations/WeightedMode.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// キーフレーム(AnimationSampleサンプル…時間の中のある点)
		struct Keyframe
		{
			float time;			// キーフレーム
			float value;		// 使用する値
			float inTangent;	// アンカーポイントの傾き
			float inWeight;		// ウェイト
			float outTangent;	// アンカーポイントの傾き
			float outWeight;	// ウェイト
			WeightedMode mode;	// weight計算方式

			Keyframe() noexcept;
			Keyframe(float time, float value) noexcept;
			Keyframe(float time, float value, float inTangent, float inWeight, float outTangent, float outWeight) noexcept;

			// モードに適して値取得
			float GetValue() const;
		};
	}
}