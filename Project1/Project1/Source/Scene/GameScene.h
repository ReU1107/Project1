#pragma once
#include "../Engine/SceneManagement/Scene.h"

class GameScene : public Engine::SceneManagement::Scene
{
private:
	using base = Engine::SceneManagement::Scene;
public:
	// コンストラクタ
	GameScene();
	// デストラクタ
	virtual ~GameScene();


	// 処理開始時に呼ばれる処理
	virtual void OnStart() override;
	// 起動時に呼ばれる処理
	virtual void OnAwake() override;

	// このシーンで使用するレンダリングパス登録
	virtual void OnRegisterRenderingPass() override;

	virtual void OnSetPhysicsScene() override;

};
