#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

namespace Engine
{
	struct Vector4 : public DirectX::XMFLOAT4
	{
		static const Vector4 Identity;

		Vector4()
			: DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}
		Vector4(float x, float y, float z, float w)
			: DirectX::XMFLOAT4(x, y, z, w)
		{
		}

		Vector4(const Vector3& vector3)
		{
			x = vector3.x;
			y = vector3.y;
			z = vector3.z;
			w = 1.0f;
		}

		Vector4(const DirectX::XMFLOAT3& vector3)
		{
			x = vector3.x;
			y = vector3.y;
			z = vector3.z;
			w = 1.0f;
		}
	};
}