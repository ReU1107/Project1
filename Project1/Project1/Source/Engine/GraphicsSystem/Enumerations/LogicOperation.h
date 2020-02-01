#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class LogicOperation : uint8_t
		{
			Clear,			// クリア
			Set,			// 設定
			Copy,			// コピー
			InvertedCopy,	// 反転コピー
			None,			// なにもしない
			Inverted,		// 反転
			And,			// 論理AND演算子
			NotAnd,			// 論理NAND演算子
			Or,				// 論理OR演算子
			NotOr,			// 論理NOR演算子
			ExclusiveOr,	// 論理XOR演算子
			Equivalent,		// 論理等価
			AndReverse,		// 
			AndInverted,	// 
			OrReverse,		//
			OrInverted,		// 
		};
	}
}