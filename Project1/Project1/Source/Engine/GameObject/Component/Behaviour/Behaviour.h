#pragma once
#include "../Component.h"

namespace Engine
{

	class Behaviour : public Component
	{
	private:
		using base = Component;
	private:
		bool m_enabled;				// このビヘイビアが有効か否か
	protected:
		// コンストラクタ
		Behaviour(const std::string & name) noexcept;
		// デストラクタ
		virtual ~Behaviour() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Behaviour; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Behaviour; }

	};
}