#pragma once
#include "../Engine/GraphicsSystem/GraphicsPass/RaytracingPass.h"

class RaytracingTestPass : public Engine::GraphicsSystem::RaytracingPass
{
private:
	using base = Engine::GraphicsSystem::RaytracingPass;
public:
	// コンストラクタ
	RaytracingTestPass();
	// デストラクタ
	virtual ~RaytracingTestPass();

	// 初期化
	virtual void OnInitialize() override;

	// 実行
	virtual void OnDispatch() override;

};
