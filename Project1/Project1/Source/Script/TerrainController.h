#pragma once
#include "../Engine/Include.h"

// �n�`����(��)
class TerrainController : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
public:
	// �R���X�g���N�^
	TerrainController() noexcept;
	// �f�X�g���N�^
	virtual ~TerrainController() noexcept;

public:
	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;
};
