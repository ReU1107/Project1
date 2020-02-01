#include "BodyPart.h"
#include "../../GameObject/Component/Transform.h"
#include "../../Math/Include.h"
#include "../../GameObject/GameObject.h"

using namespace DirectX;

namespace Engine
{
	namespace AnimationSystem
	{
		BodyPart::BodyPart() noexcept
			: name()
			//, bindRotation(Vector4::Identity)
			//, bindPosition(Vector3::Zero)
			//, bindScale(1.0f, 1.0f, 1.0f)
			, targetObject(nullptr)
		{
		}
	}
}