#pragma once
#include "../Engine/GameObject/Component/Include.h"

namespace Engine
{
	class Transform;
}

// カメラ制御
class CameraController final : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	std::shared_ptr<Engine::Transform> m_target;// ターゲットになるオブジェクト(Follow)時所持
	float m_longitude;		// 経度(単位:ラジアン)
	float m_latitude;		// 緯度(単位:ラジアン)
	float m_distance;		// 距離
	float m_speed;			// 回転速度(単位:ラジアン)
public:
	// コンストラクタ
	CameraController() noexcept;

	// デストラクタ
	virtual ~CameraController() noexcept;
public:
	virtual void OnAwake() override;

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;
};
