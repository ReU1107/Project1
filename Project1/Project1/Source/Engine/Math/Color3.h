#pragma once
#include <cstdint>

namespace Engine
{
	struct Color3
	{
		union
		{
			struct {
				float r;	// 
				float g;	// 
				float b;	// 
			};
			float array[3];
		};

		Color3() = default;

		Color3(float r, float g, float b)
			: r(r), g(g), b(b)
		{}
		Color3(uint8_t r, uint8_t g, uint8_t b)
			: r(r), g(g), b(b)
		{}
		Color3(uint32_t rgb)
		{
			r = static_cast<float>(rgb >> 24);
			g = static_cast<float>((rgb & 0x00ff0000) >> 16);
			b = static_cast<float>((rgb & 0x0000ff00) >> 8);
		}
		// ������Z�q(�����Ȃ��Ă��p�ӂ���Ă���)
		Color3& operator =(const Color3& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			return *this;
		}

		// �������Z�q�I�[�o�[���[�h
		// ���Z
		Color3& operator +=(const Color3& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			return *this;
		}
		// ���Z
		Color3& operator -=(const Color3& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			return *this;
		}
		// ��Z
		Color3& operator *=(const Color3& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			return *this;
		}
		// ���Z
		Color3& operator /=(const Color3& resource)
		{
			this->r /= resource.r;
			this->g /= resource.g;
			this->b /= resource.b;
			return *this;
		}
	};
}