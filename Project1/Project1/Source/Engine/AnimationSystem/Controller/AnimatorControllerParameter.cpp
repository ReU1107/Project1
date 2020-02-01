#include "AnimatorControllerParameter.h"
namespace Engine 
{
	namespace AnimationSystem
	{
		AnimatorControllerParameter::AnimatorControllerParameter() noexcept
			: m_parameter(nullptr)
			, m_defaultFloat(0.0f)
			, m_defaultBool(false)
			, m_defaultInt(0)
			, m_type()
		{
		}

		AnimatorControllerParameter::~AnimatorControllerParameter() noexcept
		{
		}
	}
}
