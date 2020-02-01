#pragma once
#include "../Engine/GameObject/Component/Behaviour/MonoBehaviour.h"


class BoneDisplay : public Engine::MonoBehaviour
{
private:
	using base = Engine::MonoBehaviour;
private:

public:
	// コンストラクタ
	BoneDisplay();
	// デストラクタ
	virtual ~BoneDisplay();

	virtual void OnStart() override;

	// 更新処理
	virtual void OnUpdate(float deltaTime) override;
};
