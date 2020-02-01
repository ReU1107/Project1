#pragma once
#include "Component.h"

namespace Engine
{
	class SoftBody final : public Component
	{
	private:
		using base = Component;

	public:
		// �R���X�g���N�^
		SoftBody() noexcept;
		// �f�X�g���N�^
		virtual ~SoftBody() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::SoftBody; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID()const override { return InstanceID::SoftBody; }

	};
}