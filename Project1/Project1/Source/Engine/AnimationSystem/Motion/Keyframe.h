#pragma once
#include "../Enumerations/WeightedMode.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// �L�[�t���[��(AnimationSample�T���v���c���Ԃ̒��̂���_)
		struct Keyframe
		{
			float time;			// �L�[�t���[��
			float value;		// �g�p����l
			float inTangent;	// �A���J�[�|�C���g�̌X��
			float inWeight;		// �E�F�C�g
			float outTangent;	// �A���J�[�|�C���g�̌X��
			float outWeight;	// �E�F�C�g
			WeightedMode mode;	// weight�v�Z����

			Keyframe() noexcept;
			Keyframe(float time, float value) noexcept;
			Keyframe(float time, float value, float inTangent, float inWeight, float outTangent, float outWeight) noexcept;

			// ���[�h�ɓK���Ēl�擾
			float GetValue() const;
		};
	}
}