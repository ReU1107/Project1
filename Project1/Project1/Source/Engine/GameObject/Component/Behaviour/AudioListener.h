#pragma once
#include "Behaviour.h"

namespace Engine
{
	class AudioListener final : public Behaviour
	{
	private:
		using base = Behaviour;

	public:
		AudioListener() noexcept;

		virtual ~AudioListener() noexcept;

		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::AudioListener; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::AudioListener; }
	};

}