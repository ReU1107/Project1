#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

class PathTracingPass : Engine::GraphicsSystem::RaytracingPass
{
private:
	using base = Engine::GraphicsSystem::RaytracingPass;
private:
public:
	// コンストラクタ
	PathTracingPass();
	// デストラクタ
	virtual ~PathTracingPass();

};