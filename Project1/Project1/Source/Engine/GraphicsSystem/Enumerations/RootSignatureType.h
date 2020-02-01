#pragma once
#include <cstdint>

/*
ルートシグネチャをラスタライズ法で使用するなら
必ずグローバルにする必要がある
レイトレーシング法なら
両方使う可能性がある
*/

namespace Engine 
{

	namespace GraphicsSystem 
	{
		// ルートシグネチャをレイトレーシングのどちらとして使用するか
		enum class RootSignatureType : uint8_t
		{
			Global,	// グローバル
			Local,	// ローカル
		};
	}
}
