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
		// ‘ã“ü‰‰ŽZŽq(‘‚©‚È‚­‚Ä‚à—pˆÓ‚³‚ê‚Ä‚¢‚é)
		Color3& operator =(const Color3& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			return *this;
		}

		// •¡‡‰‰ŽZŽqƒI[ƒo[ƒ[ƒh
		// ‰ÁŽZ
		Color3& operator +=(const Color3& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			return *this;
		}
		// Œ¸ŽZ
		Color3& operator -=(const Color3& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			return *this;
		}
		// æŽZ
		Color3& operator *=(const Color3& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			return *this;
		}
		// œŽZ
		Color3& operator /=(const Color3& resource)
		{
			this->r /= resource.r;
			this->g /= resource.g;
			this->b /= resource.b;
			return *this;
		}
	};
}