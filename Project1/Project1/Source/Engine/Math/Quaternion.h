#pragma once
#include "Vector3.h"
#include <utility>

namespace Engine
{

	/*
	x,y,z,w�̏��ԂŊi�[
	*/
	// �l����
	struct Quaternion
	{
		// pure imaginary // �����l����
		// pure reality // �����l����
		union {
			struct {
				Vector3 imaginary;	// ����(�x�N�g���\��)
				float real;			// ����
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
		// �����{
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

		// �����ł̏��Z
		inline Quaternion& operator/=(float real)
		{
			this->real /= real;
			this->imaginary /= real;
			return *this;
		}

		// �l�����̒���
		inline float Length() const
		{
			return (this->real * this->real) + (this->imaginary.x * this->imaginary.x) + (this->imaginary.y * this->imaginary.y) + (this->imaginary.z * this->imaginary.z);
		}
	};

	inline float QuaternionDot(const Quaternion& lhs, const Quaternion& rhs);

	/*
	���[��:Z������(x,y����)�̉�]
	�s�b�`:Y������(y,z����)�̉�]
	���[  :X������(x,z����)�̉�]
	*/
	// ���[��,�s�b�`,���[�̉�]�l����(�P�ʃ��W�A��)
	inline Quaternion QuaternionRollPitchYaw(float roll, float pitch, float yaw);

	// �����l����
	inline Quaternion QuaternionConjugate(const Quaternion& q);

	// �l�����̋t��
	inline Quaternion QuaternionInverse(const Quaternion& q);

	// �l�������ʐ��`���(Spherical Linear Interpolation)
	inline Quaternion QuaternionSlerp(const Quaternion& lhs, const Quaternion& rhs, float t);

	// �l����
	// Quaternion���e�����ꂼ��̉�]�p�x(�P��:radian)�擾
	inline Vector3 QuaternionAngle(const Quaternion& quaternion);
}
#include "QuaternionImpl.h"