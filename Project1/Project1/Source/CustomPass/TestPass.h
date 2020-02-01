#pragma once
#include "../Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

class TestPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

public:
	// �R���X�g���N�^
	TestPass();
	// �f�X�g���N�^
	virtual ~TestPass();

public:
	virtual void OnInitialize() override;

	virtual void OnRender() override;

};
