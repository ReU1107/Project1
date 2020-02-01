#pragma once
#include <DirectXMath.h>

namespace Engine 
{

	struct Matrix4x4 : public DirectX::XMFLOAT4X4
	{
		static const Matrix4x4 Identity;
		static const Matrix4x4 Zero;

		Matrix4x4()
			: DirectX::XMFLOAT4X4(0.0f, 0.0f, 0.0f, 0.0f,
							      0.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 0.0f)
		{
		}
		Matrix4x4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
			: DirectX::XMFLOAT4X4(m11,m12,m13,m14,
								  m21,m22,m23,m24,
								  m31,m32,m33,m34,
								  m41,m42,m43,m44)
		{
		}

		Matrix4x4 operator +(const Matrix4x4& other)
		{
			Matrix4x4 m = {};
			m._11 = this->_11 + other._11;
			m._12 = this->_12 + other._12;
			m._13 = this->_13 + other._13;
			m._14 = this->_14 + other._14;

			m._21 = this->_21 + other._21;
			m._22 = this->_22 + other._22;
			m._23 = this->_23 + other._23;
			m._24 = this->_24 + other._24;

			m._31 = this->_31 + other._31;
			m._32 = this->_32 + other._32;
			m._33 = this->_33 + other._33;
			m._34 = this->_34 + other._34;

			m._41 = this->_41 + other._41;
			m._42 = this->_42 + other._42;
			m._43 = this->_43 + other._43;
			m._44 = this->_44 + other._44;

			return m;
		}

		Matrix4x4& operator *=(const Matrix4x4& other)
		{
			Matrix4x4 m = {};
			m._11 = (this->_11 * other._11) + (this->_12 * other._21) + (this->_13 * other._31) + (this->_14 * other._41);
			m._12 = (this->_11 * other._12) + (this->_12 * other._22) + (this->_13 * other._32) + (this->_14 * other._42);
			m._13 = (this->_11 * other._13) + (this->_12 * other._23) + (this->_13 * other._33) + (this->_14 * other._43);
			m._14 = (this->_11 * other._14) + (this->_12 * other._24) + (this->_13 * other._34) + (this->_14 * other._44);

			m._21 = (this->_21 * other._11) + (this->_22 * other._21) + (this->_23 * other._31) + (this->_24 * other._41);
			m._22 = (this->_21 * other._12) + (this->_22 * other._22) + (this->_23 * other._32) + (this->_24 * other._42);
			m._23 = (this->_21 * other._13) + (this->_22 * other._23) + (this->_23 * other._33) + (this->_24 * other._43);
			m._24 = (this->_21 * other._14) + (this->_22 * other._24) + (this->_23 * other._34) + (this->_24 * other._44);

			m._31 = (this->_31 * other._11) + (this->_32 * other._21) + (this->_33 * other._31) + (this->_34 * other._41);
			m._32 = (this->_31 * other._12) + (this->_32 * other._22) + (this->_33 * other._32) + (this->_34 * other._42);
			m._33 = (this->_31 * other._13) + (this->_32 * other._23) + (this->_33 * other._33) + (this->_34 * other._43);
			m._34 = (this->_31 * other._14) + (this->_32 * other._24) + (this->_33 * other._34) + (this->_34 * other._44);

			m._41 = (this->_41 * other._11) + (this->_42 * other._21) + (this->_43 * other._31) + (this->_44 * other._41);
			m._42 = (this->_41 * other._12) + (this->_42 * other._22) + (this->_43 * other._32) + (this->_44 * other._42);
			m._43 = (this->_41 * other._13) + (this->_42 * other._23) + (this->_43 * other._33) + (this->_44 * other._43);
			m._44 = (this->_41 * other._14) + (this->_42 * other._24) + (this->_43 * other._34) + (this->_44 * other._44);

			return *this;
		}
	};


	inline Matrix4x4 RotateX(const Matrix4x4& base, float angle)
	{
		Matrix4x4 mat;

		return mat;
	}

	inline Matrix4x4 RotateY(const Matrix4x4& base, float angle)
	{
		Matrix4x4 mat;

		return mat;
	}

	inline Matrix4x4 RotateZ(const Matrix4x4& base, float angle)
	{
		Matrix4x4 mat;
		
		return mat;
	}
}