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
		// 代入演算子(書かなくても用意されている)
		Color3& operator =(const Color3& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			return *this;
		}

		// 複合演算子オーバーロード
		// 加算
		Color3& operator +=(const Color3& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			return *this;
		}
		// 減算
		Color3& operator -=(const Color3& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			return *this;
		}
		// 乗算
		Color3& operator *=(const Color3& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			return *this;
		}
		// 除算
		Color3& operator /=(const Color3& resource)
		{
			this->r /= resource.r;
			this->g /= resource.g;
			this->b /= resource.b;
			return *this;
		}
	};
}