#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "SkeletonBone.h"
namespace Engine
{
	namespace AnimationSystem
	{

		// Avatar(人型)オブジェクトを構成する情報
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