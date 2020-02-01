#pragma once
#include "Vector3.h"
#include <utility>

namespace Engine
{

	/*
	x,y,z,wの順番で格納
	*/
	// 四元数
	struct Quaternion
	{
		// pure imaginary // 純虚四元数
		// pure reality // 純実四元数
		union {
			struct {
				Vector3 imaginary;	// 虚数(ベクトル表現)
				float real;			// 実数
			};
			float t[4];
		};

		Quaternion()
			: imaginary(0.0f, 0.0f, 0.0f)
			, real(1.0f)
		{
		}

		Quaternion(const Vector3& imaginary, float real)
			: imaginary(imaginary)
			, real(real)
		{
		}

		inline Quaternion& operator =(const Quaternion& other)
		{
			this->real = other.real;
			this->imaginary = other.imaginary;
			return *this;
		}

		inline Quaternion operator + (const Quaternion& other) const
		{
			Quaternion q;
			q.real = this->real + other.real;
			q.imaginary.x = this->imaginary.x + other.imaginary.x;
			q.imaginary.y = this->imaginary.y + other.imaginary.y;
			q.imaginary.z = this->imaginary.z + other.imaginary.z;
			return std::move(q);
		}

		inline Quaternion operator *(float real) const
		{
			Quaternion q;
			q.real = this->real * real;
			q.imaginary.x = this->imaginary.x * real;
			q.imaginary.y = this->imaginary.y * real;
			q.imaginary.z = this->imaginary.z * real;
			return std::move(q);
		}

		inline Quaternion& operator+=(const Quaternion& other)
		{
			this->real += other.real;
			this->imaginary += other.imaginary;
			return *this;
		}
		// 実数倍
		inline Quaternion& operator*=(float real)
		{
			this->real *= real;
			this->imaginary *= real;
			return *this;
		}

		inline Quaternion& operator*=(const Quaternion& other)
		{
			const Vector3& v1 = this->imaginary;
			const Vector3& v2 = other.imaginary;
			float s1 = this->real;
			float s2 = other.real;

			this->real = (s1 * s2) - (Vector3Dot(v1, v2));
			Vector3 a;
			//a = other.imaginary * s1;
			//a+= this->imaginary * s2;
			//a+= Vector3Cross(v1,v2)
			//this->imaginary = a;
			return *this;
		}

		// 実数での除算
		inline Quaternion& operator/=(float real)
		{
			this->real /= real;
			this->imaginary /= real;
			return *this;
		}

		// 四元数の長さ
		inline float Length() const
		{
			return (this->real * this->real) + (this->imaginary.x * this->imaginary.x) + (this->imaginary.y * this->imaginary.y) + (this->imaginary.z * this->imaginary.z);
		}
	};

	inline float QuaternionDot(const Quaternion& lhs, const Quaternion& rhs);

	/*
	ロール:Z軸周り(x,y平面)の回転
	ピッチ:Y軸周り(y,z平面)の回転
	ヨー  :X軸周り(x,z平面)の回転
	*/
	// ロール,ピッチ,ヨーの回転四元数(単位ラジアン)
	inline Quaternion QuaternionRollPitchYaw(float roll, float pitch, float yaw);

	// 共役四元数
	inline Quaternion QuaternionConjugate(const Quaternion& q);

	// 四元数の逆数
	inline Quaternion QuaternionInverse(const Quaternion& q);

	// 四元数球面線形補間(Spherical Linear Interpolation)
	inline Quaternion QuaternionSlerp(const Quaternion& lhs, const Quaternion& rhs, float t);

	// 四元数
	// Quaternionより各軸それぞれの回転角度(単位:radian)取得
	inline Vector3 QuaternionAngle(const Quaternion& quaternion);
}
#include "QuaternionImpl.h"