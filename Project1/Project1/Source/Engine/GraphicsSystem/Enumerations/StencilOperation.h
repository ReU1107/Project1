#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// ステンシル値の計算
		enum class StencilOperation : uint8_t
		{
			Keep,			// ステンシルデータを保存
			Zero,			// ステンシルデータを0に設定
			Replace,		// 
			IncrementClamp,	// ステンシルを1増やし　クランプする
			DecrementClamp,	// ステンシルを1減らし　クランプする
			Invert,			// ステンシルデータを反転
			IncrementWrap,	// ステンシル値を1増やし　ラップする
			DecrementWrap,	// ステンシル値を1減らし　ラップする
		};
	}
}