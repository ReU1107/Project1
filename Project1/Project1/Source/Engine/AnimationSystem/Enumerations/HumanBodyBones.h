#pragma once
#include <cstdint>
#include <string>

namespace Engine
{
	namespace AnimationSystem
	{
		// 人型のボーン
		enum class HumanBodyBones : uint8_t
		{
			Hips,						// 尻のボーン
			LeftUpperLeg,				// 左太もものボーン
			RightUpperLeg,				// 右太もものボーン
			LeftLowerLeg,				// 左ひざのボーン
			RightLowerLeg,				// 右ひざのボーン
			LeftFoot,					// 左足首のボーン
			RightFoot,					// 右足首のボーン
			Spine,						// 背骨の第一ボーン
			Chest,						// 胸のボーン
			UpperChest,					// 胸下のボーン
			Neck,						// 首のボーン
			Head,						// 頭のボーン
			LeftShoulder,				// 左肩のボーン
			RightShoulder,				// 右肩のボーン
			LeftUpperArm,				// 左上腕のボーン
			RightUpperArm,				// 右上腕のボーン
			LeftLowerArm,				// 左ひじのボーン
			RightLowerArm,				// 右ひじのボーン
			LeftHand,					// 左手首のボーン
			RightHand,					// 右手首のボーン
			LeftToes,					// 左つま先のボーン
			RightToes,					// 右つま先のボーン
			LeftEye,					// 左目のボーン
			RightEye,					// 右目のボーン
			Jaw,						// 顎のボーン
			LeftThumbProximal,			// 左親指第一指骨のボーン
			LeftThumbIntermediate,		// 左親指第二指骨のボーン
			LeftThumbDistal,			// 左親指第三指骨のボーン
			LeftIndexProximal,			// 左人差し指第一指骨のボーン
			LeftIndexIntermediate,		// 左人差し指第二指骨のボーン
			LeftIndexDistal,			// 左人差し指第三指骨のボーン
			LeftMiddleProximal,			// 左中指第一指骨のボーン
			LeftMiddleIntermediate,		// 左中指第二指骨のボーン
			LeftMiddleDistal,			// 左中指第三指骨のボーン
			LeftRingProximal,			// 左薬指第一指骨のボーン
			LeftRingIntermediate,		// 左薬指第二指骨のボーン
			LeftRingDistal,				// 左薬指第三指骨のボーン
			LeftLittleProximal,			// 左小指第一指骨のボーン
			LeftLittleIntermediate,		// 左小指第二指骨のボーン
			LeftLittleDistal,			// 左小指第三指骨のボーン
			RightThumbProximal,			// 右親指第一指骨のボーン
			RightThumbIntermediate,		// 右親指第二指骨のボーン
			RightThumbDistal,			// 右親指第三指骨のボーン
			RightIndexProximal,			// 右人差し指第一指骨のボーン
			RightIndexIntermediate,		// 右人差し指第二指骨のボーン
			RightIndexDistal,			// 右人差し指第三指骨のボーン
			RightMiddleProximal,		// 右中指第一指骨のボーン
			RightMiddleIntermediate,	// 右中指第二指骨
			RightMiddleDistal,			// 右中指第三指骨のボーン
			RightRingProximal,			// 右薬指第一指骨のボーン
			RightRingIntermediate,		// 右薬指第二指骨のボーン
			RightRingDistal,			// 右薬指第三指骨のボーン
			RightLittleProximal,		// 右小指第一指骨のボーン
			RightLittleIntermediate,	// 右小指第二指骨のボーン
			RightLittleDistal,			// 右小指第三指骨のボーン
			LastBone,					// 区切りになる最後のボーン
		};

		HumanBodyBones HumanBoneID(const std::string& name);

	}
}