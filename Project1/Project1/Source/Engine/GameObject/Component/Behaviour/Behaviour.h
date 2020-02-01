#pragma once
#include "../Component.h"

namespace Engine
{

	class Behaviour : public Component
	{
	private:
		using base = Component;
	private:
		bool m_enabled;				// ���̃r�w�C�r�A���L�����ۂ�
	protected:
		// �R���X�g���N�^
		Behaviour(const std::string & name) noexcept;
		// �f�X�g���N�^
		virtual ~Behaviour() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Behaviour; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Behaviour; }

	};
}