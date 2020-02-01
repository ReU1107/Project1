#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Sprite;
	}
}

class GBufferDebugPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

private:
	Engine::GraphicsSystem::Sprite* m_sprite;
private:
	// �R���X�g���N�^
	GBufferDebugPass();
	// �f�X�g���N�^
	~GBufferDebugPass();
public:
	// 
	virtual void OnInitialize() override;

	// 
	virtual void OnRender() override;

};