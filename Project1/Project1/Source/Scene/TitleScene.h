#pragma once
#include "../Engine/SceneManagement/Scene.h"

class TitleScene : public Engine::SceneManagement::Scene
{
private:
	using base = Engine::SceneManagement::Scene;

public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	virtual ~TitleScene();

};
