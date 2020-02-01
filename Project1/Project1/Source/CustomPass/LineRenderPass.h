#pragma once
#include "../Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

class LineRenderPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

public:
	// コンストラクタ
	LineRenderPass();
	// デストラクタ
	virtual ~LineRenderPass();

public:
	virtual void OnInitialize() override;

	virtual void OnRender() override;

};
