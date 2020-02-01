#pragma once
#include <cstdint>

/*
D3D12_HIT_GROUP_DESC
*/

namespace Engine 
{

	namespace GraphicsSystem
	{

		enum class BottomLevelType : uint8_t;

		struct RaytracingHitGroupDesc
		{
			const wchar_t* name;					// このグループの名前
			const wchar_t* hitShader;				// レイと衝突した際に呼び出されるシェーダー
			const wchar_t* intersectShader;			// 衝突判定用シェーダー
			const wchar_t* anyHitShader;			// 
			BottomLevelType type;				// 衝突形状
			RaytracingHitGroupDesc()
				: name(nullptr), hitShader(nullptr), intersectShader(nullptr)
				, anyHitShader(nullptr), type()
			{
			}
		};

	}

}

/*
wchar_t*で持つ理由:
この構造体をunionで囲むためstd::wstringでもつことができない
*/