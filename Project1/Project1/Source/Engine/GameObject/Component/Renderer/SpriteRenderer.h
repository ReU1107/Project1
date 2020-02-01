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
		GraphicsSystem::Sprite* m_sprite;		// �\������X�v���C�g
	public:
		// �R���X�g���N�^
		SpriteRenderer() noexcept;
		// �f�X�g���N�^
		~SpriteRenderer() noexcept;
	public:
		void SetSprite(GraphicsSystem::Sprite* sprite);

	};
}

using SpriteRendererPtr = std::shared_ptr<Engine::SpriteRenderer>;