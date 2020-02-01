#include "AnimationPropertyQuaternion.h"
#include "../Avatar/Avatar.h"
#include "../Avatar/BodyPart.h"
#include "../Avatar/AvatarMask.h"
#include "../Motion/AnimationCurve.h"
#include "../Motion/Keyframe.h"
#include "../../Object.h"
#include "../../Math/Quaternion.h"

using namespace DirectX;

namespace Engine
{
	namespace AnimationSystem
	{
		AnimationPropertyQuaternion::AnimationPropertyQuaternion() noexcept
			: base(NumCurves)
		{
		}

		AnimationPropertyQuaternion::~AnimationPropertyQuaternion() noexcept
		{
		}

		void AnimationPropertyQuaternion::Update(AvatarPtr avatar, AvatarMaskPtr mask,float time, float weight)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto outputTarget = (Quaternion*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			if (!outputTarget)
				return;

			AdjacentKeyframes xKeyframes = m_curves.at(0)->GetAdjacentKeyframes(time);
			AdjacentKeyframes yKeyframes = m_curves.at(1)->GetAdjacentKeyframes(time);
			AdjacentKeyframes zKeyframes = m_curves.at(2)->GetAdjacentKeyframes(time);
			AdjacentKeyframes wKeyframes = m_curves.at(3)->GetAdjacentKeyframes(time);

			DirectX::XMVECTOR lhs = XMVectorSet(
				xKeyframes.lhs.value,
				yKeyframes.lhs.value,
				zKeyframes.lhs.value,
				wKeyframes.lhs.value
			);
			DirectX::XMVECTOR rhs = XMVectorSet(
				xKeyframes.rhs.value,
				yKeyframes.rhs.value,
				zKeyframes.rhs.value,
				wKeyframes.rhs.value
			);

			DirectX::XMVECTOR q = XMQuaternionSlerp(lhs, rhs, xKeyframes.s);
			
			DirectX::XMVECTOR qw = XMQuaternionSlerp(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), q, weight);

			DirectX::XMVECTOR qo = XMVectorSet(
				outputTarget->imaginary.x,
				outputTarget->imaginary.y, 
				outputTarget->imaginary.z, 
				outputTarget->real);

			DirectX::XMVECTOR result = DirectX::XMQuaternionMultiply(qo, qw);
			
			XMStoreFloat4((DirectX::XMFLOAT4*)outputTarget, result);
		}

		void AnimationPropertyQuaternion::Reset(AvatarPtr avatar, AvatarMaskPtr mask)
		{
			auto bodyPart = avatar->GetBodyPart(m_targetName);

			if (!bodyPart.targetObject)
				return;

			auto outputTarget = (Quaternion*)bodyPart.targetObject->GetPropertyAddress(m_propertyName);
			if (!outputTarget)
				return;

			outputTarget->imaginary.x = 0.0f;
			outputTarget->imaginary.y = 0.0f;
			outputTarget->imaginary.z = 0.0f;
			outputTarget->real = 1.0f;
		}

	}
}