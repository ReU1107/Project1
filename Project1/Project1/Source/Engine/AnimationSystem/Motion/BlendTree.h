#pragma once
#include "Motion.h"
#include "../Enumerations/BlendTreeType.h"
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{
		/*
		2�ȏ�̃A�j���[�V�������u�����h����ۂɎg�p����
		���̃N���X���g�p���Ăł��郂�[�V������
		�����^�C�����ɂ��������
		*/
		struct ChildMotion;

		class BlendTree final : public Motion
		{
		private:
			using base = Motion;
			using ChildMotions = std::vector<ChildMotion>;
			using MotionPtr = std::shared_ptr<Motion>;
		private:
			ChildMotions m_childMotions;
			BlendTreeType m_type;	// �u�����h�A���S���Y��
			bool m_isActive;
		public:
			BlendTree(const std::string& name) noexcept;
			virtual ~BlendTree() noexcept;
		private:
			// �ꎟ��Lerp�u�����f�B���O
			void OneDimensionLerp();
		public:
			bool IsActive() const { return m_isActive; }

			void Active(bool active = true) { m_isActive = active; }

			void Clear();

			// �q���[�V�����ǉ�
			void AddChild(MotionPtr motion);
			void AddChild(const ChildMotion& child);

			// �q���[�V�����폜
			void RemoveChild(uint32_t index);

			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f) override;
		};
	}
}
