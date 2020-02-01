#pragma once
#include <cstdint>

/*
If,IfNot
の時の注意事項として
Ifの条件に見たす場合
変数に入っている値が0以外の時にtrueになる
IfNotの場合
↑の逆で0の時のみtrueとしてtrueになる
*/

namespace Engine
{
	namespace AnimationSystem
	{
		enum class AnimatorConditionMode : uint8_t
		{
			If,			// パラメータ値が true のとき、条件は true になります。
			IfNot,		// パラメータ値が false のとき、条件は true になります。
			Greater,	// パラメータ値が threshold より大きいとき、条件は true になります。
			Less,		// パラメータ値が threshold の値以下のとき、条件は true になります。
			Equals,		// パラメータ値が threshold の値と等しいとき、条件は true になります。
			NotEqual,	// パラメータ値が threshold の値と等しくないとき、条件は true になります。
		};
	}
}
