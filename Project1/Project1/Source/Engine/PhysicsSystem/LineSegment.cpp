#include "LineSegment.h"
namespace Engine
{
	namespace PhysicsSystem
	{
		float LineSegment::MinDistance(const Vector3& point) const
		{
			Vector3 ab = end - start;
			Vector3 ba = ab * -1.0f;
			Vector3 ac = point - start;
			Vector3 bc = point - end;

			// 開始位置より手前側にある
			if (Vector3Dot(ab, ac) < 0.0f)
			{
				return ac.Length();
			}
			// 終了位置より奥側にある
			else if (Vector3Dot(ba, bc) < 0.0f)
			{
				return bc.Length();
			}
			// 線分の内部にある
			else
			{
				float scalar = Vector3Dot(ac, ab) / Vector3Dot(ab, ab);

				Vector3 p = ab * scalar;
				// 垂直の場所にある点との距離を求める
				return (ac - p).Length();
			}


			return 0.0f;
		}
	}
}
