#pragma once
#include "Component.h"

namespace Engine
{
	class SoftBody final : public Component
	{
	private:
		using base = Component;

	public:
		// コンストラクタ
		SoftBody() noexcept;
		// デストラクタ
		virtual ~SoftBody() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::SoftBody; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID()const override { return InstanceID::SoftBody; }

	};
}