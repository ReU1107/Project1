#pragma once
#include "../../Math/Include.h"
#include "../../InstanceID.h"

namespace Engine
{
	namespace AnimationSystem
	{

		/*
		トランスフォームそれぞれが
		アニメーションが止まった時又はアニメーションを1から再生しなおそうとしたときに
		1度Tポーズ(デフォルト)のポーズに戻らないと値がおかしくなるため
		の初期化用の値
		unityでは
		classID 137 SkinnedMeshRenderer;
		https://docs.unity3d.com/ja/current/Manual/ClassIDReference.html
		*/

		struct SkeletonBone
		{
			Vector4 rotation;	// 回転
			Vector3 position;	// 位置
			Vector3 scale;		// スケール
			InstanceID id;

			SkeletonBone();
		};
	}
}