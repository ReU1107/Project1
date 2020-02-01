#include "CurveHelper.h"
#include "Vector2.h"

namespace Engine
{

	void DeCasteljauAlgorithm(Vector2& destination, const std::vector<Vector2>& controllPoint, uint32_t controllCount, float interpolation)
	{
		for (uint32_t i = 0; i < controllCount; ++i) {
			for (uint32_t j = 0; j < 3; j++) {
				Vector2 a = Vector2Multiplication(controllPoint[j], 1.0f - interpolation);
				Vector2 b = Vector2Multiplication(controllPoint[j + 1], interpolation);

			}
		}
	}


}