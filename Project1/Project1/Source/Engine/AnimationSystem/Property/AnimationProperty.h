#pragma once
#include <vector>
#include <string>
#include <memory>

namespace Engine
{
	class Object;

	namespace AnimationSystem
	{
		// �O���錾
		class Avatar;
		class AvatarMask;
		class AnimationCurve;

		// �A�j���[�V�����v���p�e�B(�A�j���[�V��������)
		class AnimationProperty
		{
		private:
			using AnimationCurves = std::vector<AnimationCurve*>;
			using ObjectPtr = std::shared_ptr<Object>;
		protected:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;

		protected:
			AnimationCurves m_curves;	// �A�j���[�V�����J�[�u�z��
			std::string m_propertyName;	// 
			std::string m_targetName;	// 
			ObjectPtr m_targetObject;	// 
		public:
			// �R���X�g���N�^
			AnimationProperty(size_t elementCount) noexcept;
			// �f�X�g���N�^
			virtual ~AnimationProperty() noexcept;
		public:
			// �\�[�g
			float Sort();

			// �N���A
			void Clear();

			// �������\��̃I�u�W�F�N�g�̕ϐ����ݒ�
			void SetTargetPropertyName(const std::string& name);

			// 
			void SetTargetName(const std::string& name) { m_targetName = name; }

			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) = 0;

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) = 0;

			// �A�j���[�V�����J�[�u�擾
			AnimationCurve* GetCurve(const std::string& name) const;

			// �A�j���[�V�����J�[�u�擾
			AnimationCurve* GetCurve(uint32_t index) const;

			// �A�j���[�V�����J�[�u�z��擾
			AnimationCurves& GetCurves();

		};
	}
}

/*
	private:
		using AnimationCurves = std::unordered_map<std::string, AnimationCurve *>;
	private:
		AnimationCurves m_curves;	// �J�[�u�z��
*/

		//// 
		//void TransformUpdate(const BodyPart & part, float frame);
		//// 
		//void SkinnedMeshRendererUpdate(const BodyPart & part, float frame);

		//void BlendShapeUpdate();

		//// �}�e���A���̒l��ύX
		//void MaterialUpdate();

