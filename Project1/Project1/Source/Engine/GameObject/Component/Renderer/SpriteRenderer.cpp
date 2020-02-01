#include "SpriteRenderer.h"

namespace Engine
{
	using namespace GraphicsSystem;
	SpriteRenderer::SpriteRenderer() noexcept
		: base("SpriteRenderer")
		, m_sprite(nullptr)
	{
	}

	SpriteRenderer::~SpriteRenderer() noexcept
	{
	}

	void SpriteRenderer::SetSprite(Sprite* sprite)
	{
		m_sprite = sprite;
	}

}