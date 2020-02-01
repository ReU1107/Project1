#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

namespace Engine
{
	inline Vector3 Vector3TransformCoord(const Vector3& vec, const Matrix4x4& mat)
	{
		Vector3 result;
		result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31 + 1.0f * mat._41;
		result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32 + 1.0f * mat._42;
		result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33 + 1.0f * mat._43;

		return result;
	}

	// w成分を無視する
	inline Vector3 Vector3TransformNormal(const Vector3& vec, const Matrix4x4& mat)
	{
		Vector3 result;
		result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31;
		result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32;
		result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33;

		return result;
	}

	inline bool Matrix4x4EulerAnglesXYZ(const Matrix4x4& mat, Vector3* vec)
	{
		// ジンバルロック判定
		if (mat.m[0][2] > 1.0f - MathF::Epsilon || mat.m[0][2] < -1.0f + MathF::Epsilon)
		{
			vec->x = 0.0f;
			vec->y = (mat.m[0][2] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			vec->z = -atan2f(-mat.m[1][0], mat.m[1][1]);
			return false;
		}

		vec->y = -asinf(mat.m[0][2]);
		vec->x = asinf(mat.m[1][2] / cosf(vec->y));
		// ジンバルロック判定
		if (MathF::IsNotANumber(vec->x))
		{
			vec->x = 0.0f;
			vec->y = (mat.m[0][2] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			vec->z = -atan2f(-mat.m[1][0], mat.m[1][1]);
			return false;
		}

		if (mat.m[2][2] < 0.0f)
		{
			vec->x = MathF::PI - (vec->x);
		}

		vec->z = atan2f(mat.m[0][1], mat.m[0][0]);
		return true;
	}

	inline bool Matrix4x4EulerAnglesYZX(const Matrix4x4& mat, Vector3* vec)
	{
		// ジンバルロック判定
		if (mat.m[1][0] > 1.0f - MathF::Epsilon || mat.m[1][0] < -1.0f + MathF::Epsilon)
		{
			vec->x = -atan2f(-mat.m[2][1], mat.m[2][2]);
			vec->y = 0.0f;
			vec->z = (mat.m[1][0] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			return false;
		}

		vec->z = -asinf(mat.m[1][0]);
		vec->y = asinf(mat.m[2][0] / cosf(vec->z));

		// ジンバルロック判定
		if (MathF::IsNotANumber(vec->y))
		{
			vec->x = -atan2f(-mat.m[2][1], mat.m[2][2]);
			vec->y = 0.0f;
			vec->z = (mat.m[1][0] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			return false;
		}

		if (mat.m[0][0] < 0.0f)
		{
			vec->y = MathF::PI - (vec->y);
		}

		vec->x = atan2f(mat.m[1][2], mat.m[1][1]);
		return true;
	}

	inline bool Matrix4x4EulerAnglesZXY(const Matrix4x4& mat, Vector3* vec)
	{
		// ジンバルロック判定
		if (mat.m[2][1] > 1.0f - MathF::Epsilon || mat.m[2][1] < -1.0f + MathF::Epsilon)
		{
			vec->x = (mat.m[2][1] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			vec->y = atan2f(-mat.m[0][2], mat.m[0][0]);
			vec->z = 0.0f;
			return false;
		}

		vec->x = -asinf(mat.m[2][1]);
		vec->z = asinf(mat.m[0][1] / cosf(vec->x));

		// ジンバルロック判定
		if (MathF::IsNotANumber(vec->z))
		{
			vec->x = (mat.m[2][1] < 0) ? MathF::PIDiv2 : -MathF::PIDiv2;
			vec->y = atan2f(-mat.m[0][2], mat.m[0][0]);
			vec->z = 0.0f;
			return false;
		}
		if (mat.m[1][1] < 0.0f)
		{
			vec->z = MathF::PI - (vec->z);
		}

		vec->y = atan2f(mat.m[2][0], mat.m[2][2]);

		return true;
	}
}