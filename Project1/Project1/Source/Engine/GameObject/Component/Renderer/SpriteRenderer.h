#pragma once
#include "Renderer.h"
namespace Engine
{
	namespace GraphicsSystem
	{
		class Sprite;
	}

	class SpriteRenderer final : public Renderer
	{
	private:
		using base = Renderer;
	private:
		GraphicsSystem::Sprite* m_sprite;		// 表示するスプライト
	public:
		// コンストラクタ
		SpriteRenderer() noexcept;
		// デストラクタ
		~SpriteRenderer() noexcept;
	public:
		void SetSprite(GraphicsSystem::Sprite* sprite);

	};
}

using SpriteRendererPtr = std::shared_ptr<Engine::SpriteRenderer>;