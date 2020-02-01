#pragma once
#include "Quaternion.h"

namespace Engine
{

	float QuaternionDot(const Quaternion& lhs, const Quaternion& rhs)
	{
		return 0.0f;
	}

	Quaternion QuaternionRollPitchYaw(float roll, float pitch, float yaw)
	{
		// それぞれの軸の四元数作成後に合成
		Quaternion rQuaternion;
		roll /= 2;
		rQuaternion.real = cosf(roll);
		rQuaternion.imaginary.z = sinf(roll);

		Quaternion yQuaternion;
		pitch /= 2;
		yQuaternion.real = cosf(pitch);
		yQuaternion.imaginary.y = sinf(pitch);

		Quaternion xQuaternion;
		yaw /= 2;
		xQuaternion.real = cosf(yaw);
		xQuaternion.imaginary.x = sinf(yaw);

		return Quaternion();
	}

	inline Quaternion QuaternionConjugate(const Quaternion& q)
	{
		// 虚数部分を反転したもの
		Quaternion conj;
		conj.real = q.real;
		conj.imaginary.x = -q.imaginary.x;
		conj.imaginary.y = -q.imaginary.y;
		conj.imaginary.z = -q.imaginary.z;

		return conj;
	}

	inline Quaternion QuaternionInverse(const Quaternion& q)
	{
		Quaternion inv;
		float length = q.Length();

		// 共役を大きさの二乗で割ったもの
		//inv = QuaternionConjugate(q);
		//inv /= length;
		return inv;
	}

	Quaternion QuaternionSlerp(const Quaternion& lhs, const Quaternion& rhs, float t)
	{
		/*
		引数の四元数が単位四元数として考える
		*/

		float angle = QuaternionDot(lhs, rhs);
		float a = acosf(angle);

		Quaternion q;

		float b = sin((1 - t) * a) / sin(a);
		float c = sin(t * a) / sin(a);

		q = (lhs * b) + (rhs * c);

		return q;
	}

	Vector3 QuaternionAngle(const Quaternion& quaternion)
	{
		DirectX::XMFLOAT4X4 matrix;
		DirectX::XMVECTOR q = DirectX::XMVectorSet(
			quaternion.imaginary.x, 
			quaternion.imaginary.y,
			quaternion.imaginary.z,
			quaternion.real);

		DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixRotationQuaternion(q));

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
}