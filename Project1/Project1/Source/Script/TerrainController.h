#pragma once
#include "../Engine/Include.h"

// 地形操作(仮)
class TerrainController : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
public:
	// コンストラクタ
	TerrainController() noexcept;
	// デストラクタ
	virtual ~TerrainController() noexcept;

public:
	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;
};
