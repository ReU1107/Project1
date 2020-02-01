#pragma once
#include "../Engine/GameObject/Component/Include.h"

class PMXBoneController : public Engine::MonoBehaviour
{
private:
	std::shared_ptr<Engine::IKBone> m_ik;

public:
	// コンストラクタ
	PMXBoneController();
	// デストラクタ
	virtual ~PMXBoneController();

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnLateUpdate(float deltaTime) override;

};
