#include "Avatar.h"
#include "BodyPart.h"

namespace Engine
{
	namespace AnimationSystem
	{
		Avatar::Avatar() noexcept
			: base("Avatar")
			, m_isHuman(true)
		{
		}

		Avatar::~Avatar() noexcept
		{
			m_bodyParts.clear();
		}

		uint32_t Avatar::GetTransformCount() const
		{
			return (uint32_t)m_bodyParts.size();
		}

		//Transform * Avatar::GetBoneTransform(HumanBodyBones humanBoneID) const
		//{
		//	const auto & it = m_bodyParts.find(humanBoneID);
		//	if (it != m_bodyParts.cend()) {
		//		return (*it).second.transform;
		//	}
		//	return nullptr;
		//}

		BodyPart Avatar::GetBodyPart(const std::string& name)
		{
			const auto& it = m_bodyParts.find(name);
			if (it == m_bodyParts.cend())
			{
				return BodyPart();
			}
			return (*it).second;
		}

		Avatar::BodyParts& Avatar::GetBodyParts()
		{
			return m_bodyParts;
		}
	}
}