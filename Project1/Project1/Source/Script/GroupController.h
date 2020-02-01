#pragma once
#include "../Engine/GameObject/Include.h"

class GroupController : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour();

private:
	TransformPtr m_cameraTransform;
public:
	GroupController();
	// 
	virtual ~GroupController();

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

};
