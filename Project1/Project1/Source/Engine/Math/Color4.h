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
				float r;	// 赤
				float g;	// 緑
				float b;	// 青
				float a;	// 透明度
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

		// 代入演算子(書かなくても用意されている)
		Color4& operator =(const Color4& resource)
		{
			this->r = resource.r;
			this->g = resource.g;
			this->b = resource.b;
			this->a = resource.a;
			return *this;
		}

		// 複合演算子オーバーロード
		// 加算
		Color4& operator +=(const Color4& resource)
		{
			this->r += resource.r;
			this->g += resource.g;
			this->b += resource.b;
			this->a += resource.a;
			return *this;
		}
		// 減算
		Color4& operator -=(const Color4& resource)
		{
			this->r -= resource.r;
			this->g -= resource.g;
			this->b -= resource.b;
			this->a -= resource.a;
			return *this;
		}
		// 乗算
		Color4& operator *=(const Color4& resource)
		{
			this->r *= resource.r;
			this->g *= resource.g;
			this->b *= resource.b;
			this->a *= resource.a;
			return *this;
		}
		// 除算
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