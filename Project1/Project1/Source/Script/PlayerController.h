#pragma once
#include "../Engine/Include.h"

namespace Engine 
{
	class Transform;
	class Animator;
}
// プレイヤー制御
class PlayerController final : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	std::shared_ptr<Engine::Transform> m_cameraTransform;
	bool m_shift;
public:
	std::string m_motionFile;
	std::string m_morphFile;
public:
	// コンストラクタ
	PlayerController() noexcept;
	// デストラクタ
	virtual ~PlayerController() noexcept;

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;
};
