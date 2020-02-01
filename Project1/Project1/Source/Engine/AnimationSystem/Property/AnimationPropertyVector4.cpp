#include "AnimationPropertyVector4.h"
#include "../Avatar/Avatar.h"
#include "../Avatar/BodyPart.h"
#include "../Avatar/AvatarMask.h"
#include "../Motion/AnimationCurve.h"
#include "../Motion/Keyframe.h"
#include "../../Object.h"
#include "../../Math/Vector4.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationPropertyVector4::AnimationPropertyVector4() noexcept
			: base(NumCurves)
		{
		}

		AnimationPropertyVector4::~AnimationPropertyVector4() noexcept
		{
		}

		void AnimationPropertyVector4::Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight)
		{
			assert(!"");
		}
	}
}