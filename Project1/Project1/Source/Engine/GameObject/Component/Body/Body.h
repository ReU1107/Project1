#pragma once
#include "../Component.h"

namespace Engine
{
	class Body : public Component
	{
	private:
		using base = Component;

	public:
		// �R���X�g���N�^
		Body() noexcept;
		// �f�X�g���N�^
		virtual ~Body() noexcept;

	};
}