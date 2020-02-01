#pragma once
#include "../Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

class RaytracingTestPass : public Engine::GraphicsSystem::RaytracingPass
{
private:
	using base = Engine::GraphicsSystem::RaytracingPass;
public:
	// �R���X�g���N�^
	RaytracingTestPass();
	// �f�X�g���N�^
	virtual ~RaytracingTestPass();

	// ������
	virtual void OnInitialize() override;

	// ���s
	virtual void OnDispatch() override;

};
