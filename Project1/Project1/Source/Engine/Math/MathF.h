#pragma once

namespace Engine
{

	struct MathF
	{

		// 限りなく0に近い値
		static constexpr float Epsilon = 0.00001f;
		// 無限小数
		static constexpr float Infinity = 3.402823466e+38f;
		// 負の無限小数
		static constexpr float NegativeInfinity = -Infinity;
		// 円周率
		static constexpr float PI = 3.14159265359f;
		// 
		static constexpr float PI2 = PI * 2.0f;
		// 
		static constexpr float PIDiv2 = PI / 2.0f;

		// ラジアンから度
		static constexpr float RadToDeg = 360.0f / (PI * 2);
		// 度からラジアン
		static constexpr float DegToRad = (PI * 2) / 360.0f;

		// ほぼゼロか否か
		inline static bool NearZero(float value);

		// 度からラジアンに変換
		inline static float ConvertDegreeToRadian(float degree);

		// ラジアンから度に変換
		inline static float ConvertRadianToDegree(float radian);

		// 非数かどうか
		inline static bool IsNotANumber(float value);

		// 大きい方を返す
		inline static float Max(float lhs, float rhs);

		// 小さい方を返す
		inline static float Min(float lhs, float rhs);

		// 範囲制限
		inline static float Clamp(float source, float max, float min);

		// ブレンド係数
		inline static float BlendCoefficient(float current, float left, float right);

		// コサイン
		inline static float Cos(float angle);
		// サイン
		inline static float Sin(float angle);
		//タンジェント
		inline static float Tan(float angle);

		// アークコサイン
		inline static float ACos(float);
		// アークサイン
		inline static float ASin(float);
		// アークタンジェント
		inline static float ATan(float);
		inline static float ATan2(float, float);
	};
}
// 実装
#include "MathFImpl.h"