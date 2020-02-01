#include "AnimatorCondition.h"

namespace Engine
{
	namespace AnimationSystem
	{

		AnimatorCondition::AnimatorCondition(void* parameter, AnimatorConditionMode mode, float threshold)
			: parameter(parameter)
			, threshold(threshold)
			, mode(mode)
		{
		}

		bool AnimatorCondition::Compare()
		{
			switch (mode)
			{
			case AnimatorConditionMode::If:
				if (*((bool*)parameter)) 
				{
					return true;
				}
				break;
			case AnimatorConditionMode::IfNot:
				if (*((bool*)parameter) == false)
				{
					return true;
				}
				break;
			case AnimatorConditionMode::Greater:
				if (*((float*)parameter) >= threshold) 
				{
					return true;
				}
				break;
			case AnimatorConditionMode::Less:
				if (*((float*)parameter) <= threshold) 
				{
					return true;
				}
				break;
			case AnimatorConditionMode::Equals:
				if (*((float*)parameter) == threshold) 
				{
					return true;
				}
				break;
			case AnimatorConditionMode::NotEqual:
				if (*((float*)parameter) != threshold) 
				{
					return true;
				}
				break;
			default:
				break;
			}

			return false;
		}
	}
}
