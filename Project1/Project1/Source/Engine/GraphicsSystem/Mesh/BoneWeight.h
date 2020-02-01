#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// 頂点のボーン影響情報
		struct BoneWeight
		{
			uint32_t boneIndex0;	// 1 つめのボーンのインデックス
			uint32_t boneIndex1;	// 2 つめのボーンのインデックス
			uint32_t boneIndex2;	// 3 つめのボーンのインデックス
			uint32_t boneIndex3;	// 4 つめのボーンのインデックス
			float weight0;			// 1 つめのボーンでスキニングしているウェイト
			float weight1;			// 2 つめのボーンでスキニングしているウェイト
			float weight2;			// 3 つめのボーンでスキニングしているウェイト
			float weight3;			// 4 つめのボーンでスキニングしているウェイト

			BoneWeight& operator=(const BoneWeight& other)
			{
				this->boneIndex0 = other.boneIndex0;
				this->boneIndex1 = other.boneIndex1;
				this->boneIndex2 = other.boneIndex2;
				this->boneIndex3 = other.boneIndex3;
				this->weight0 = other.weight0;
				this->weight1 = other.weight1;
				this->weight2 = other.weight2;
				this->weight3 = other.weight3;
				return *this;
			}
		};
	}
}