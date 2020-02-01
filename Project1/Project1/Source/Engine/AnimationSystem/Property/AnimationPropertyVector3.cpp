#include "AnimationPropertyVector3.h"
#include "../Avatar/Avatar.h"
#include "../Avatar/BodyPart.h"
#include "../Avatar/AvatarMask.h"
#include "../Motion/AnimationCurve.h"
#include "../Motion/Keyframe.h"
#include "../../Object.h"
#include "../../Math/Vector3.h"

using namespace DirectX;

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationPropertyVector3::AnimationPropertyVector3() noexcept
			: base(NumCurves)
		{
		}

		AnimationPropertyVector3::~AnimationPropertyVector3() noexcept
		{
		}

		void AnimationPropertyVector3::Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto outputTarget = (Vector3*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			if (!outputTarget)
				return;

			auto xKeyframes = m_curves.at(0)->GetAdjacentKeyframes(time);
			auto yKeyframes = m_curves.at(1)->GetAdjacentKeyframes(time);
			auto zKeyframes = m_curves.at(2)->GetAdjacentKeyframes(time);

			auto lhs = XMVectorSet(
				xKeyframes.lhs.value,
				yKeyframes.lhs.value,
				zKeyframes.lhs.value,
				0.0f
			);
			auto rhs = XMVectorSet(
				xKeyframes.rhs.value,
				yKeyframes.rhs.value,
				zKeyframes.rhs.value,
				0.0f
			);

			auto v = DirectX::XMVectorLerp(lhs, rhs, xKeyframes.s);

			outputTarget->x += XMVectorGetX(v) * weight;
			outputTarget->y += XMVectorGetY(v) * weight;
			outputTarget->z += XMVectorGetZ(v) * weight;

		}

		void AnimationPropertyVector3::Reset(AvatarPtr avatar, AvatarMaskPtr mask)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto outputTarget = (Vector3*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			if (!outputTarget)
				return;
			outputTarget->x = 0.0f;
			outputTarget->y = 0.0f;
			outputTarget->z = 0.0f;
		}
	}
}