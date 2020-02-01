#pragma once
#include "../Engine/GameObject/Include.h"

namespace Engine 
{
	class Transform;
}

// 光源制御
class LightController final : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:
	float m_longitude;		// 経度(単位:ラジアン)
	float m_latitude;		// 緯度(単位:ラジアン)
	float m_distance;		// 距離
	float m_speed;			// 回転速度(単位:ラジアン)
public:
	// コンストラクタ
	LightController() noexcept;

	// デストラクタ
	virtual ~LightController() noexcept;
public:


};