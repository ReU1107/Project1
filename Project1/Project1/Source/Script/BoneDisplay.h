#pragma once
#include "../Engine/GameObject/Component/Behaviour/MonoBehaviour.h"


class BoneDisplay : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:

public:
	// �R���X�g���N�^
	BoneDisplay();
	// �f�X�g���N�^
	virtual ~BoneDisplay();

	virtual void OnStart() override;

	// �X�V����
	virtual void OnUpdate(float deltaTime) override;
};
