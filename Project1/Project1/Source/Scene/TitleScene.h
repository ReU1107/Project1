#pragma once
#include "../Engine/SceneManagement/Scene.h"

class TitleScene : public Engine::SceneManagement::Scene
{
private:
	using base = Engine::SceneManagement::Scene;

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	virtual ~TitleScene();

};
