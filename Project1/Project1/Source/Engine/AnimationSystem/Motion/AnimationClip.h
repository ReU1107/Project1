#pragma once
#include "Motion.h"
#include <unordered_map>
#include "../Enumerations/WrapMode.h"
#include "../../Utility/FrameRate.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// �O���錾
		class AnimationCurve;
		class AnimationProperty;
		class AnimationEvent;
		class Avatar;
		class AvatarMask;
		struct BodyPart;

		class AnimationClip final : public Motion
		{
		private:
			using base = Motion;
			using AnimationProperties = std::unordered_map<std::string, AnimationProperty*>;
			using AnimationEvents = std::vector<AnimationEvent*>;
		private:
			AnimationProperties m_properties;	// �A�j���[�V�����v���p�e�B�z��
			AnimationEvents m_events;			// �C�x���g�z��

			float m_frameRate;					// �t���[�����[�g
			float m_startTime;					// �A�j���[�V�����J�n�t���[��
			float m_endTime;					// �A�j���[�V�����I���t���[��
			float m_lastTime;					// ���̃A�j���[�V�����̍Ō�̃t���[��
			WrapMode m_wrapMode;				// �t���[���O��
			FPS m_fps;							// �Đ��t���[�����[�g
		public:
			// �R���X�g���N�^
			AnimationClip(const std::string& name) noexcept;
			// �f�X�g���N�^
			virtual ~AnimationClip() noexcept;
		public:
			// �A�j���[�V�����v���p�e�B�ǉ�
			void AddProperty(const std::string& relativePath, const std::string& propertyName, AnimationProperty* property);
			AnimationProperty* AddProperty(const std::string& relativePath, TypeID componentID, const std::string& propertyName);

			void AddProperty(const std::string& name, AnimationProperty* prop);

			// �A�j���[�V�����C�x���g�ǉ�
			void AddEvent(AnimationEvent* animationEvent);

			// fps�ݒ�
			void SetFPS(FPS fps = FPS::Thirty);
			// �J�n�t���[���ݒ�
			void SetStartTime(float startTime);
			// �L�[�t���[���z����̍Ō�̎��Ԑݒ�
			void SetEndTime(float endTime);
			// �I�������鎞�Ԃ̐ݒ�
			void SetLastTime(float lastTime);

			// �A�j���[�V�����v���p�e�B�擾
			AnimationProperty* GetProperty(const std::string& name);

			// �A�j���[�V�����v���p�e�B���擾
			uint32_t GetPropertyCount() const;

			// �t���[�����[�g�擾
			float GetFrameRate() const;

			// �A�j���[�V�����̒����擾(�P��:�~���b)
			float GetLength() const;

			// �t���[���ԍ��Ń\�[�g
			void Sort();

			// �v���p�e�B,�J�[�u�폜
			void Clear();

			// �X�V
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;

		};
	}
}
	//// �{�[����,�t���[���ԍ���胂�[�V�����f�[�^�擾
	//bool GetKeyframe(Keyframe & keyframe, const std::string & boneName, uint32_t frameIndex);