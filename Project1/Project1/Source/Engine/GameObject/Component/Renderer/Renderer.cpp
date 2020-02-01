#include "Renderer.h"

namespace Engine
{

	Renderer::Renderer(const std::string& name) noexcept
		: base(name)
		, m_shadowCastingMode(ShadowCastingMode::On)
		, m_enabled(true)
	{
	}

	Renderer::~Renderer() noexcept
	{
	}

	void Renderer::SetShadowCastingMode(ShadowCastingMode mode)
	{
		m_shadowCastingMode = mode;
	}

	bool Renderer::CastingShadow()
	{
		return m_shadowCastingMode == ShadowCastingMode::Off ? false : true;
	}

	bool Renderer::IsView()
	{
		return m_enabled;
	}

	void Renderer::Enable(bool enable)
	{
		m_enabled = enable;
	}

	ShadowCastingMode Renderer::GetShadowCastingMode() const
	{
		return m_shadowCastingMode;
	}

}