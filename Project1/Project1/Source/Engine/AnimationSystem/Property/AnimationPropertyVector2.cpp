#include "AnimationPropertyVector2.h"
#include "../Avatar/Avatar.h"
#include "../Avatar/BodyPart.h"
#include "../Avatar/AvatarMask.h"
#include "../Motion/AnimationCurve.h"
#include "../Motion/Keyframe.h"
#include "../../Object.h"
#include "../../Math/Quaternion.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationPropertyVector2::AnimationPropertyVector2() noexcept
			: base(NumCurves)
		{
		}

		AnimationPropertyVector2::~AnimationPropertyVector2() noexcept
		{
		}

		void AnimationPropertyVector2::Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight)
		{
			assert(!"");

		}

	}
}