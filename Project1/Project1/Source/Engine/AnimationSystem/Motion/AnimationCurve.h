#pragma once
#include <vector>
#include "../Enumerations/WrapMode.h"
#include "Keyframe.h"

namespace Engine
{
	namespace AnimationSystem
	{

		enum class InterpolationType
		{
			Constant,	// �萔
			Linear,		// ���`
			EaseInOut,	// �C�[�Y�C���A�E�g
		};

		struct AdjacentKeyframes
		{
			Keyframe lhs;			// 
			Keyframe rhs;			// 
			float s;				// 2�̃L�[�t���[���Ԃ̊��� s : (1 -s)
			bool isSingleKeyframe;	// �L�[�t���[����������Ȃ����ߕ�ԕs�v(lhs�̂ݎg�p���Ă�������)

		};

		// �L�[�t���[���̏W���̂�����
		class AnimationCurve final
		{
		private:
			using Keyframes = std::vector<Keyframe>;
		private:
			Keyframes m_keyframes;		// �L�[�t���[���z��
			float m_endTime;			// �L�[�t���[���z�񂪏I��鎞��
			WrapMode m_preWrapMode;		// 
			WrapMode m_postWrapMode;	// 
			bool m_keyframesIsDirty;	// �L�[�t���[�������ω�����
		public:
			// �R���X�g���N�^
			AnimationCurve() noexcept;
			// �f�X�g���N�^
			~AnimationCurve() noexcept;

		public:
			// �L�[�t���[�����擾
			uint32_t GetKeyframeCount() const;

			// �L�[�t���[���ǉ�
			void AddKeyframe(const Keyframe& key);
			// �L�[�t���[���폜
			void RemoveKeyframe(uint32_t index);
			// �L�[�t���[������ւ�
			void MoveKeyframe(uint32_t index, const Keyframe& key);

			// �L�[�t���[���Őݒ肵���t���[���ԍ����ɕ��ёւ�
			float Sort();
			// time���̒l�擾
			float Evaluate(float time) const;

			AdjacentKeyframes GetAdjacentKeyframes(float time) const;

			void Clear();
			// []
			Keyframe& At(uint32_t index);
			// operator[]���Z�q�I�[�o�[���[�h
			Keyframe& operator[](uint32_t index);

			//// ��Ԗ���
			//static AnimationCurve* Constant(float timeStart, float timeEnd, float value);
			//// �C�[�Y�C���C�[�Y�A�E�g
			//static AnimationCurve* EaseInOut(float timeStart, float valueStart, float timeEnd, float valueEnd);
			//// ���`���
			//static AnimationCurve* Linear(float timeStart, float valueStart, float timeEnd, float valueEnd);
		};
	}
}
