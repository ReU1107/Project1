#pragma once
#include "../Component.h"
namespace Engine
{

	class Filter : public Component
	{
	private:
		using base = Component;
	public:
		// �R���X�g���N�^
		Filter(const std::string& name) noexcept;
		// �f�X�g���N�^
		virtual ~Filter() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Filter; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Filter; }

	};
}