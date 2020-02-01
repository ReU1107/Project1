#pragma once
#include "../Component.h"
#include "Enumerations/ShadowCastingMode.h"
#include <iostream>

namespace Engine
{
	// �S�Ẵ����_���[�̊��N���X
	class Renderer : public Component
	{
	private:
		using base = Component;
	private:
		ShadowCastingMode m_shadowCastingMode;	// �V���h�E�L���X�e�B���O���@
		bool m_enabled;							// �\�����邩�ۂ�
	public:
		// �R���X�g���N�^
		Renderer(const std::string& name) noexcept;
		// �f�X�g���N�^
		virtual ~Renderer() noexcept;
	public:
		// ID�擾
		static const InstanceID ID() { return InstanceID::Renderer; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Renderer; }

		// �e
		void SetShadowCastingMode(ShadowCastingMode mode);

		// �e�𗎂Ƃ���
		bool CastingShadow();
		// �\������邩
		bool IsView();

		void Enable(bool enable);

		// �e�𗎂Ƃ���
		ShadowCastingMode GetShadowCastingMode() const;

	};
}