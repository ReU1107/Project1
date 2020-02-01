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

		// インスタンスID
		static const InstanceID ID() { return InstanceID::AudioListener; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::AudioListener; }
	};

}