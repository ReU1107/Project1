#pragma once
#include "../Enumerations/AnimatorConditionMode.h"

/*
ポインターの扱い方は
何かしらの型のポインターにキャストしてから
実体化させる必要がある
理由:
void * は実体化できないから
*/

namespace Engine
{

	namespace AnimationSystem
	{

		struct AnimatorCondition
		{
			void* parameter;			// パラメーター
			float threshold;			// しきい値(比較対象)
			AnimatorConditionMode mode;	// 比較方法

			AnimatorCondition(void* parameter, AnimatorConditionMode mode, float threshold);

			// 比較する
			bool Compare();
		};
	}
}

