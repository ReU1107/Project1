#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"
/*
�v��Z�p�X
*/
class PreZPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

public:
	// �R���X�g���N�^
	PreZPass();
	// �f�X�g���N�^
	virtual ~PreZPass();
	// ������
	virtual void OnInitialize() override;
	// �`��
	virtual void OnRender() override;

};