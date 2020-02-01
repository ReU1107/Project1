#pragma once
#include "MathF.h"
#include <cmath>

namespace Engine
{
	inline bool MathF::NearZero(float value)
	{
		// â‘Î’l‚ªŒÀ‚è‚È‚­ƒ[ƒ‚É‹ß‚¢
		if (fabsf(value) <= Epsilon)
		{
			return true;
		}

		return false;
	}

	inline float MathF::ConvertDegreeToRadian(float degree)
	{
		return degree * PI / 180.0f;
	}

	inline float MathF::ConvertRadianToDegree(float radian)
	{
		return radian * 180.0f / PI;
	}

	inline bool MathF::IsNotANumber(float value)
	{
		if (std::isnan<float>(value))
			return true;

		return false;
	}

	inline float MathF::Max(float lhs, float rhs)
	{
		return (lhs > rhs) ? lhs : rhs;
	}

	inline float MathF::Min(float lhs, float rhs)
	{
		return (lhs < rhs) ? lhs : rhs;
	}

	inline float MathF::Clamp(float source, float max, float min)
	{
		float destination = source;
		if (source > max) 
		{
			destination = max;
		}
		else if (source < min) 
		{
			destination = min;
		}
		return destination;
	}

	inline float MathF::BlendCoefficient(float current, float left, float right)
	{
		float blend = 0.0f;

		const float numerator = current - left;
		const float denominator = right - left;

		blend = numerator / denominator;

		return blend;
	}

	inline float MathF::Cos(float angle)
	{
		return 0.0f;
	}

	inline float MathF::Sin(float angle)
	{
		return 0.0f;
	}

	inline float MathF::Tan(float angle)
	{
		return 0.0f;
	}

	inline float MathF::ACos(float)
	{
		return 0.0f;
	}

	inline float MathF::ASin(float)
	{
		return 0.0f;
	}

	inline float MathF::ATan(float)
	{
		return 0.0f;
	}

	inline float MathF::ATan2(float, float)
	{
		return 0.0f;
	}

}