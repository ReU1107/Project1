#pragma once
#include <cstdint>
#include <string>

namespace Engine
{
	namespace AnimationSystem
	{
		// �l�^�̃{�[��
		enum class HumanBodyBones : uint8_t
		{
			Hips,						// �K�̃{�[��
			LeftUpperLeg,				// ���������̃{�[��
			RightUpperLeg,				// �E�������̃{�[��
			LeftLowerLeg,				// ���Ђ��̃{�[��
			RightLowerLeg,				// �E�Ђ��̃{�[��
			LeftFoot,					// ������̃{�[��
			RightFoot,					// �E����̃{�[��
			Spine,						// �w���̑��{�[��
			Chest,						// ���̃{�[��
			UpperChest,					// �����̃{�[��
			Neck,						// ��̃{�[��
			Head,						// ���̃{�[��
			LeftShoulder,				// �����̃{�[��
			RightShoulder,				// �E���̃{�[��
			LeftUpperArm,				// ����r�̃{�[��
			RightUpperArm,				// �E��r�̃{�[��
			LeftLowerArm,				// ���Ђ��̃{�[��
			RightLowerArm,				// �E�Ђ��̃{�[��
			LeftHand,					// �����̃{�[��
			RightHand,					// �E���̃{�[��
			LeftToes,					// ���ܐ�̃{�[��
			RightToes,					// �E�ܐ�̃{�[��
			LeftEye,					// ���ڂ̃{�[��
			RightEye,					// �E�ڂ̃{�[��
			Jaw,						// �{�̃{�[��
			LeftThumbProximal,			// ���e�w���w���̃{�[��
			LeftThumbIntermediate,		// ���e�w���w���̃{�[��
			LeftThumbDistal,			// ���e�w��O�w���̃{�[��
			LeftIndexProximal,			// ���l�����w���w���̃{�[��
			LeftIndexIntermediate,		// ���l�����w���w���̃{�[��
			LeftIndexDistal,			// ���l�����w��O�w���̃{�[��
			LeftMiddleProximal,			// �����w���w���̃{�[��
			LeftMiddleIntermediate,		// �����w���w���̃{�[��
			LeftMiddleDistal,			// �����w��O�w���̃{�[��
			LeftRingProximal,			// ����w���w���̃{�[��
			LeftRingIntermediate,		// ����w���w���̃{�[��
			LeftRingDistal,				// ����w��O�w���̃{�[��
			LeftLittleProximal,			// �����w���w���̃{�[��
			LeftLittleIntermediate,		// �����w���w���̃{�[��
			LeftLittleDistal,			// �����w��O�w���̃{�[��
			RightThumbProximal,			// �E�e�w���w���̃{�[��
			RightThumbIntermediate,		// �E�e�w���w���̃{�[��
			RightThumbDistal,			// �E�e�w��O�w���̃{�[��
			RightIndexProximal,			// �E�l�����w���w���̃{�[��
			RightIndexIntermediate,		// �E�l�����w���w���̃{�[��
			RightIndexDistal,			// �E�l�����w��O�w���̃{�[��
			RightMiddleProximal,		// �E���w���w���̃{�[��
			RightMiddleIntermediate,	// �E���w���w��
			RightMiddleDistal,			// �E���w��O�w���̃{�[��
			RightRingProximal,			// �E��w���w���̃{�[��
			RightRingIntermediate,		// �E��w���w���̃{�[��
			RightRingDistal,			// �E��w��O�w���̃{�[��
			RightLittleProximal,		// �E���w���w���̃{�[��
			RightLittleIntermediate,	// �E���w���w���̃{�[��
			RightLittleDistal,			// �E���w��O�w���̃{�[��
			LastBone,					// ��؂�ɂȂ�Ō�̃{�[��
		};

		HumanBodyBones HumanBoneID(const std::string& name);

	}
}