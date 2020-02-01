#pragma once
#include <cstdint>

namespace Engine
{
	namespace AnimationSystem
	{
		// アニメーションのフレーム外の処理方法
		enum class WrapMode : uint8_t
		{
			Once,			// タイムがアニメーションの最後に達すると、クリップは自動的にプレイを停止し、タイムがクリップの始めにリセットされる
			Loop,			// タイムがアニメーションクリップの最後に達すると、タイムは最初に戻りループする
			PingPong,		// タイムがアニメーションクリップの最後に達すると、タイムは始めと終わりの間をピンポンのように行き来する
			Default,		// 前もって設定していた状態を使用します。
			ClampForever,	// 通常の再生が行われた後、最後のフレームのアニメーションが再生され続けることになり停止することはありません
		};

	}
}