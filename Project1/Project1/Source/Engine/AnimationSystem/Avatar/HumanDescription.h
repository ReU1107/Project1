#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "SkeletonBone.h"
namespace Engine
{
	namespace AnimationSystem
	{

		// Avatar(�l�^)�I�u�W�F�N�g���\��������
		struct HumanDescription
		{
			uint32_t skeletonCount;
			std::unordered_map<std::string, SkeletonBone> skeletonBones;
			HumanDescription()
				: skeletonCount(0)
			{
			}
		};
	}
}