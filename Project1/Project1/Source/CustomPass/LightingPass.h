#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"
#include "../Engine/Include.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Sprite;
	}
}

class LightingPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;
private:
	::RenderTexturePtr m_normal;
	::RenderTexturePtr m_albedo;
	::RenderTexturePtr m_diffuse;
	::RenderTexturePtr m_specular;
	std::shared_ptr<Engine::GraphicsSystem::Texture> m_shadow;
	::DepthTexturePtr m_depth;
	Engine::GraphicsSystem::Sprite* m_sprite;
public:
	// コンストラクタ
	LightingPass();
	// デストラクタ
	~LightingPass();

	virtual void OnInitialize() override;

	virtual void OnRender() override;
};