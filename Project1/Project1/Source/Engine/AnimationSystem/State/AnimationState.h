#pragma once
#include <cstdint>
#include "../..//Utility/Timer.h"

namespace Engine
{
	class Transform;

	namespace AnimationSystem
	{
		// �O���錾
		class AnimationClip;
		/*
		������Ԃ̃A�j���[�V���� ���̂悤�ȏ�Ԃ�\����{AnimationState�Ɉ��AnimationClip
		�A�j���[�V�����u�����h������Ƃ��͂ǂ����邩���̏��������Ă��Ȃ�
		*/
		/*
		m_isUpdate�X�V���K�v��
		���m�ɂ̓t���[��index�͐i��ł���
		�g�����Ƃ��Ă�
		�J�����ɉf���Ă��Ȃ��Ƃ��ɃA�j���[�V���������Ȃ��Ă�����
		�J�����ɉf��Ȃ��Ɣ��f���ꂽ��false
		�t���[��index�͐i��ł����true�ɂȂ�����Ԃ̃A�j���[�V��������K�������
		*/
		// ��̏�Ԃ̃A�j���[�V����
		class AnimationState final
		{
		private:
			AnimationClip* m_clip;		// �Đ����悤�Ƃ��Ă���A�j���[�V����
			float m_speed;				// �Đ����x
			uint32_t m_loopCount;		// ���[�v��
			Timer m_timer;				// ���[�J�����Ԏ�
			uint32_t m_frameIndex;
			bool m_isUpdate;			// �X�V���K�v��
		public:
			// �R���X�g���N�^
			AnimationState() noexcept;
			// �f�X�g���N�^
			~AnimationState() noexcept;
		public:
			// �A�j���[�V������K�p����g�����X�t�H�[���ǉ�
			void AddMixingTransform(Transform* transform, bool recursive = true);

			// �A�j���[�V�����N���b�v�ݒ�
			void SetAnimationClip(AnimationClip* clip);

			void SetSpeed(float speed = 1.0f);

		public:
			// �ݒ肳�ꂽ�g�����X�t�H�[�����폜
			void RemoveMixingTransform(Transform* transform);

			//private:
			//	// FK����
			//	void ForwardKinematics(GameObject * gameObject);
			//
			//	// IK����
			//	void InverseKinematics(GameObject * gameObject);
			//
		public:
			void Play();

			void Update(float deltaTime);

			void Stop();
		};
	}
}