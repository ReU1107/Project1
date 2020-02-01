#include "CameraController.h"
#include "../Engine/Include.h"

using namespace DirectX;
using namespace Engine;

CameraController::CameraController() noexcept
	: base("CameraController")
	, m_target(nullptr)
	, m_latitude(XMConvertToRadians(45.0f))
	, m_longitude(XMConvertToRadians(180.0f))
	, m_distance(50.0f)
	, m_speed(XMConvertToRadians(5.0f))
{
}

CameraController::~CameraController() noexcept
{
}

void CameraController::OnAwake()
{
}

void CameraController::OnStart()
{
	m_target = GameObject::Find("グループ")->GetTransform();
	auto camera = AddComponent<Camera>();
	camera->SetFarClipPlane(10000.0f);
}

void CameraController::OnUpdate(float deltaTime)
{
	if (GetKeyState('W') & 0x8000) 
	{
		m_latitude += m_speed;
		m_latitude = m_latitude >= XMConvertToRadians(89.0f) ? XMConvertToRadians(89.0f) : m_latitude;
	}
	if (GetKeyState('S') & 0x8000) 
	{
		m_latitude -= m_speed;
		m_latitude = m_latitude <= XMConvertToRadians(-89.0f) ? XMConvertToRadians(-89.0f) : m_latitude;
	}
	if (GetKeyState('A') & 0x8000) 
	{
		m_longitude += m_speed;
	}
	if (GetKeyState('D') & 0x8000) 
	{
		m_longitude -= m_speed;
	}
	if (GetKeyState('O') & 0x8000) 
	{
		m_distance += (m_speed * 80);
	}
	if (GetKeyState('P') & 0x8000) 
	{
		m_distance -= (m_speed * 80);
	}

	// 緯度回転
	float latSin, latCos;
	XMScalarSinCos(&latSin, &latCos, m_latitude);
	const Vector3 latPosition = { m_distance * latCos,m_distance * latSin,0.0f };

	// 経度回転
	float lonSin, lonCos;
	XMScalarSinCos(&lonSin, &lonCos, m_longitude);
	const Vector3 lonPosition = { latPosition.x * lonSin,latPosition.y,latPosition.x * lonCos };

	Vector3 targetPos = m_target->GetWorldPosition();
	targetPos.y += 15;
	Vector3 position = targetPos + lonPosition;

	auto transform = GetTransform();

	transform->SetWorldPosition(position);
	transform->LookAt(targetPos);
	
}
