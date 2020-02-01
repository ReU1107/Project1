#include "AnimationPropertyFloat.h"
#include "../Avatar/Avatar.h"
#include "../Avatar/BodyPart.h"
#include "../Avatar/AvatarMask.h"
#include "../Motion/AnimationCurve.h"
#include "../Motion/Keyframe.h"
#include "../../Object.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationPropertyFloat::AnimationPropertyFloat() noexcept
			: base(NumCurves)
		{
		}
		
		AnimationPropertyFloat::~AnimationPropertyFloat() noexcept
		{
		}

		void AnimationPropertyFloat::Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto value = m_curves.at(0)->Evaluate(time);

			auto outputTarget = (float*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			
			*outputTarget += value * weight;

		}

		void AnimationPropertyFloat::Reset(AvatarPtr avatar, AvatarMaskPtr mask)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto outputTarget = (float*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			*outputTarget = 0.0f;
		}

	}
}