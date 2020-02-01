#pragma once
#include "../Component.h"

namespace Engine
{
	class Body : public Component
	{
	private:
		using base = Component;

	public:
		// コンストラクタ
		Body() noexcept;
		// デストラクタ
		virtual ~Body() noexcept;

	};
}