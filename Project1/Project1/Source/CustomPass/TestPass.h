#pragma once
#include "../Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

class TestPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

public:
	// コンストラクタ
	TestPass();
	// デストラクタ
	virtual ~TestPass();

public:
	virtual void OnInitialize() override;

	virtual void OnRender() override;

};
