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

			// �J�n�ʒu����O���ɂ���
			if (Vector3Dot(ab, ac) < 0.0f)
			{
				return ac.Length();
			}
			// �I���ʒu��艜���ɂ���
			else if (Vector3Dot(ba, bc) < 0.0f)
			{
				return bc.Length();
			}
			// �����̓����ɂ���
			else
			{
				float scalar = Vector3Dot(ac, ab) / Vector3Dot(ab, ab);

				Vector3 p = ab * scalar;
				// �����̏ꏊ�ɂ���_�Ƃ̋��������߂�
				return (ac - p).Length();
			}


			return 0.0f;
		}
	}
}
