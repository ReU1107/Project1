#include "GroupController.h"
#include "../Engine/Include.h"

using namespace Engine;

GroupController::GroupController()
{
}

GroupController::~GroupController()
{
}

void GroupController::OnStart()
{
	GetTransform()->SetWorldPosition(Vector3(0.0f, 0.0f, -100.0f));

	m_cameraTransform = GameObject::Find("ƒƒCƒ“ƒJƒƒ‰")->GetTransform();
}

void GroupController::OnUpdate(float deltaTime)
{
	static const float speed = 10.0f;
	auto transform = GetTransform();
	Vector3 position = transform->GetLocalPosition();

	Vector3 forward = m_cameraTransform->Forward();
	Vector3 left = m_cameraTransform->Left();

	// y¬•ªœ‹Ž
	forward.y = 0.0f;
	left.y = 0.0f;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		position += forward * speed;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		position -= forward * speed;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		position += left * speed;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		position -= left * speed;
	}
	if (GetKeyState('U') & 0x8000)
	{
		position.y += 0.5f * speed;
	}

	transform->SetLocalPosition(position);

}
