#pragma once
#include <cstdint>
/*
多分
1次元Lerpブレンディング
2次元Lerpブレンディング
三角形2次元Lerpブレンディング
一般化2次元Lerpブレンディング
*/

/*
1次元の場合2つのアニメーションをブレンドできる
ブレンド係数は1つもう1つは1.0 - 1つ目のブレンド係数
2次元の場合3,4つのアニメーションをブレンドできる
ブレンド係数は2つ

*/

namespace Engine
{
	namespace AnimationSystem
	{
		// アニメーションブレンディングアルゴリズム
		enum class BlendTreeType : uint8_t
		{
			Simple1D,				// 単一パラメータの型を使用した基本的なブレンディング
			SimpleDirectional2D,	// モーションが異なる向きを表す場合に最適。
			FreeformDirectional2D,	// このブレンドタイプは、モーションが異なる向きを表すときに使われます
			FreeformCartesian2D,	// モーションが異なる向きを表さない場合に最適です。
			Direct,					// 各ノードのブレンディングウェイトを直接ユーザーが制御することができます
		};
	}
}