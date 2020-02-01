#pragma once
#include "../Component.h"
namespace Engine
{

	class Filter : public Component
	{
	private:
		using base = Component;
	public:
		// コンストラクタ
		Filter(const std::string& name) noexcept;
		// デストラクタ
		virtual ~Filter() noexcept;
	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Filter; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Filter; }

	};
}