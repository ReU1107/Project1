#include "Keyframe.h"

namespace Engine
{
	namespace AnimationSystem
	{
		Keyframe::Keyframe() noexcept
			: time(0.0f)
			, value(0.0f)
			, inTangent(0.0f)
			, inWeight(0.0f)
			, outTangent(0.0f)
			, outWeight(0.0f)
			, mode(WeightedMode::None)
		{
		}

		Keyframe::Keyframe(float time, float value) noexcept
			: time(time)
			, value(value)
			, inTangent(0.0f)
			, inWeight(0.0f)
			, outTangent(0.0f)
			, outWeight(0.0f)
			, mode(WeightedMode::None)
		{
		}

		Keyframe::Keyframe(float time, float value, float inTangent, float inWeight, float outTangent, float outWeight) noexcept
			: time(time)
			, value(value)
			, inTangent(inTangent)
			, inWeight(inWeight)
			, outTangent(outTangent)
			, outWeight(outWeight)
			, mode(WeightedMode::None)
		{
		}

		float Keyframe::GetValue() const
		{
			float value = this->value;
			switch (this->mode)
			{
			case WeightedMode::None:
				break;
			case WeightedMode::In:
				value *= this->inWeight;
				break;
			case WeightedMode::Out:
				value *= this->outWeight;
				break;
			case WeightedMode::Both:
				value *= this->inWeight;
				value *= this->outWeight;
				break;
			default:
				break;
			}

			return value;
		}
	}
}