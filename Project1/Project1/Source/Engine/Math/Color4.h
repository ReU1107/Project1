#pragma once
#include "Color3.h"

namespace Engine
{
	struct Color4
	{
		static const Color4 Black;
		static const Color4 Gray;
		static const Color4 White;
		static const Color4 Red;
		static const Color4 Green;
		static const Color4 Blue;
		static const Color4 Yellow;
		static const Color4 Cyan;
		static const Color4 Magenta;

		union
		{
			struct
			{
				float r;	// ��
				float g;	// ��
				float b;	// ��
				float a;	// �����x
			};
			float array[4];
		};


		Color4() = default;

		Color4(float r, float g, float b, float a)
			: r(r), g(g), b(b), a(a)
		{}

		Color4(const Color3& rgb, float a = 1.0f)
			: r(rgb.r), g(rgb.g), b(rgb.g), a(a)
		{}

		// ������Z�q(�����Ȃ��Ă��p�ӂ���Ă���)
		Color4& operator =(const Color4& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			this->a = resource.a;
			return *this;
		}

		// �������Z�q�I�[�o�[���[�h
		// ���Z
		Color4& operator +=(const Color4& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			this->a += resource.a;
			return *this;
		}
		// ���Z
		Color4& operator -=(const Color4& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			this->a -= resource.a;
			return *this;
		}
		// ��Z
		Color4& operator *=(const Color4& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			this->a *= resource.a;
			return *this;
		}
		// ���Z
		Color4& operator /=(const Color4& resource)
		{
			this->r /= resource.r;
			this->g /= resource.g;
			this->b /= resource.b;
			this->a /= resource.a;
			return *this;
		}
	};

}