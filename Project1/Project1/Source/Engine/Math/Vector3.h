#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Matrix4x4.h"
#include "MathF.h"

namespace Engine
{
	struct Vector3 : DirectX::XMFLOAT3
	{
		static const Vector3 Zero;

		Vector3()
			: DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)
		{
		}

		Vector3(float x, float y, float z)
			: DirectX::XMFLOAT3(x, y, z)
		{
		}

		inline Vector3 operator+(const Vector3& other) const
		{
			Vector3 v;
			v.x = this->x + other.x;
			v.y = this->y + other.y;
			v.z = this->z + other.z;
			return v;
		}
		inline Vector3 operator-(const Vector3& other) const
		{
			Vector3 v;
			v.x = this->x - other.x;
			v.y = this->y - other.y;
			v.z = this->z - other.z;
			return v;
		}

		inline Vector3 operator*(const Vector3& other) const
		{
			Vector3 v;
			v.x = this->x * other.x;
			v.y = this->y * other.y;
			v.z = this->z * other.z;
			return v;
		}

		inline Vector3 operator/(const Vector3& other) const
		{
			Vector3 v;
			v.x = this->x / other.x;
			v.y = this->y / other.y;
			v.z = this->z / other.z;
			return v;
		}

		inline Vector3 operator+(float other) const
		{
			Vector3 v;
			v.x = this->x + other;
			v.y = this->y + other;
			v.z = this->z + other;
			return v;
		}

		inline Vector3 operator-(float other) const
		{
			Vector3 v;
			v.x = this->x - other;
			v.y = this->y - other;
			v.z = this->z - other;
			return v;
		}

		inline Vector3 operator*(float other) const
		{
			Vector3 v;
			v.x = this->x * other;
			v.y = this->y * other;
			v.z = this->z * other;
			return v;
		}

		inline Vector3 operator/(float other) const
		{
			Vector3 v;
			v.x = this->x / other;
			v.y = this->y / other;
			v.z = this->z / other;
			return v;
		}

		inline Vector3 operator+=(const Vector3& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		inline Vector3& operator-=(const Vector3& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		inline Vector3& operator*=(const Vector3& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		inline Vector3& operator/=(const Vector3& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}

		inline Vector3& operator+=(float other)
		{
			this->x += other;
			this->y += other;
			this->z += other;
			return *this;
		}

		inline Vector3& operator-=(float other)
		{
			this->x -= other;
			this->y -= other;
			this->z -= other;
			return *this;
		}

		inline Vector3& operator*=(float other)
		{
			this->x *= other;
			this->y *= other;
			this->z *= other;
			return *this;
		}

		inline Vector3& operator/=(float other)
		{
			this->x /= other;
			this->y /= other;
			this->z /= other;
			return *this;
		}

		inline bool operator<(const Vector3& other)
		{
			float l = this->LengthSq();
			float r = other.LengthSq();
			// ベクトルの長さ比較(小さいなら)
			if (l < r)
			{
				return true;
			}

			return false;
		}

		inline bool operator>(const Vector3& other)
		{
			float l = this->LengthSq();
			float r = other.LengthSq();
			// ベクトルの長さ比較(大きいなら)
			if (l > r)
			{
				return true;
			}

			return false;
		}

		float LengthSq() const
		{
			return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
		}

		float Length() const
		{
			return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

	};

	inline float Vector3Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return rhs.x * lhs.x + rhs.y * lhs.y + rhs.z * lhs.z;
	}

	inline Vector3 Vector3Cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = Vector3::Zero;
		//vec.x = rhs.y * lhs.z - rhs.z * lhs.y;
		//vec.y = rhs.z * lhs.x - rhs.x * lhs.z;
		//vec.z = rhs.x * lhs.y - rhs.y * lhs.x;

		vec.x = lhs.y * rhs.z - lhs.z * rhs.y;
		vec.y = lhs.z * rhs.x - lhs.x * rhs.z;
		vec.z = lhs.x * rhs.y - lhs.y * rhs.x;

		return vec;
	}

	inline Vector3 Vector3Normalize(const Vector3& vec)
	{
		return vec / vec.Length();
	}

	// 
	inline bool Vector3IsNotANumber(const Vector3& vec)
	{
		if (std::isnan<float>(vec.x))
		{
			return true;
		}
		if (std::isnan<float>(vec.y))
		{
			return true;
		}
		if (std::isnan<float>(vec.z))
		{
			return true;
		}
		return false;
	}

	inline Vector3 Vector3Clamp(const Vector3& vec, const Vector3& max, const Vector3& min)
	{
		Vector3 result = Vector3::Zero;
		result.x = MathF::Clamp(vec.x, max.x, min.x);
		result.y = MathF::Clamp(vec.y, max.y, min.y);
		result.z = MathF::Clamp(vec.z, max.z, min.z);

		return result;
	}

	inline Vector3 MatrixAngle(const Matrix4x4& matrix)
	{
		float sinX = -matrix._32;
		if (sinX > 1 - 1.0e-5f)
		{
			return Vector3(0.0f, 0.0f, 0.0f);
		}
		float angleX = asinf(sinX);
		float cosX = cosf(angleX);

		float sinY = matrix._31 / cosX;
		float cosY = matrix._33 / cosX;
		float angleY = atan2f(sinY, cosY);

		float sinZ = matrix._12 / cosX;
		float cosZ = matrix._22 / cosX;
		float angleZ = atan2f(sinZ, cosZ);

		return Vector3(angleX, angleY, angleZ);
	}

	inline Vector3 Vector3NormalizeEuler(const Vector3& euler)
	{
		Vector3 vec = euler;
		if (vec.x < -MathF::PI || MathF::PI < vec.x)
		{
			if (vec.x > 0)
			{
				vec.x -= MathF::PI * 2;
			}
			else
			{
				vec.x += MathF::PI * 2;
			}
		}
		if (vec.y < -MathF::PI * 0.5f || MathF::PI * 0.5f < vec.y)
		{
			if (vec.y > 0)
			{
				vec.y -= MathF::PI * 2;
			}
			else
			{
				vec.y += MathF::PI * 2;
			}
		}
		if (vec.z < -MathF::PI || MathF::PI < vec.z)
		{
			if (vec.z > 0)
			{
				vec.z -= MathF::PI * 2;
			}
			else
			{
				vec.z += MathF::PI * 2;
			}
		}

		return vec;
	}
}