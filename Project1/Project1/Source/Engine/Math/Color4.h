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
				float r;	// Ô
				float g;	// —Î
				float b;	// Â
				float a;	// “§–¾“x
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

		// ‘ã“ü‰‰ŽZŽq(‘‚©‚È‚­‚Ä‚à—pˆÓ‚³‚ê‚Ä‚¢‚é)
		Color4& operator =(const Color4& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			this->a = resource.a;
			return *this;
		}

		// •¡‡‰‰ŽZŽqƒI[ƒo[ƒ[ƒh
		// ‰ÁŽZ
		Color4& operator +=(const Color4& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			this->a += resource.a;
			return *this;
		}
		// Œ¸ŽZ
		Color4& operator -=(const Color4& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			this->a -= resource.a;
			return *this;
		}
		// æŽZ
		Color4& operator *=(const Color4& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			this->a *= resource.a;
			return *this;
		}
		// œŽZ
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