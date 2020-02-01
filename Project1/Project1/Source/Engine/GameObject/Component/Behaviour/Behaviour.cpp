#include "Behaviour.h"
namespace Engine
{

	Behaviour::Behaviour(const std::string & name) noexcept
		: base(name)
		, m_enabled(true)
	{
	}

	Behaviour::~Behaviour() noexcept
	{
	}
}