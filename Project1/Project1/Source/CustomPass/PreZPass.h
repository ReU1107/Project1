#pragma once
#include "..//Engine/GraphicsSystem/GraphicsPass/RenderingPass.h"
/*
プリZパス
*/
class PreZPass : public Engine::GraphicsSystem::RenderingPass
{
private:
	using base = Engine::GraphicsSystem::RenderingPass;

public:
	// コンストラクタ
	PreZPass();
	// デストラクタ
	virtual ~PreZPass();
	// 初期化
	virtual void OnInitialize() override;
	// 描画
	virtual void OnRender() override;

};