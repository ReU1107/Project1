#include "AvatarMask.h"
#include "Avatar.h"
#include "../../Utility/EnumOperator.h"

namespace Engine
{
	namespace AnimationSystem
	{
		AvatarMask::AvatarMask(const std::string& name) noexcept
			: base(name)
			, m_baseAvatar(nullptr)
			, m_transformCount(0)
			, m_maskPart()
		{
		}

		AvatarMask::~AvatarMask() noexcept
		{

		}

		void AvatarMask::SetAvatar(AvatarPtr avatar)
		{
			m_baseAvatar = avatar;
			m_transformCount = avatar->GetTransformCount();
		}

		void AvatarMask::AddMaskBodyPart(AvatarMaskBodyPart part)
		{
			m_maskPart |= part;
		}

		AvatarMaskBodyPart AvatarMask::GetMaskBodyPart()
		{
			return m_maskPart;
		}

		uint32_t AvatarMask::GetTransformCount() const
		{
			return m_transformCount;
		}

	}
}