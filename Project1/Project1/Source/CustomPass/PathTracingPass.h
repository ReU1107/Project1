#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

class PathTracingPass : Engine::GraphicsSystem::RaytracingPass
{
private:
	using base = Engine::GraphicsSystem::RaytracingPass;
private:
public:
	// �R���X�g���N�^
	PathTracingPass();
	// �f�X�g���N�^
	virtual ~PathTracingPass();

};