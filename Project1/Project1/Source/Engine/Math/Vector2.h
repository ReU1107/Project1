#pragma once
#include <DirectXMath.h>

namespace Engine
{
	struct Vector2 : DirectX::XMFLOAT2
	{
		Vector2()
			: DirectX::XMFLOAT2(0.0f, 0.0f)
		{
		}

		Vector2(float x, float y)
			: DirectX::XMFLOAT2(x, y)
		{
		}
	};

	inline Vector2 Vector2Multiplication(const Vector2& v, float scalar)
	{
		return Vector2();
	}

}