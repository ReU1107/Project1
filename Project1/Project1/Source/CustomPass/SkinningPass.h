#pragma once
#include "../Engine/GraphicsSystem/Include.h"

/*
スキニングを行う
コンピュートパス

スキニング処理のいらない
メッシュの描画中に非同期で実行しておく
*/
namespace Engine
{
	namespace SceneManagement
	{
		class Scene;
	}
}

class SkinningPass : public Engine::GraphicsSystem::ComputePass
{
private:
	using base = Engine::GraphicsSystem::ComputePass;

	Engine::SceneManagement::Scene* m_belongScene;

public:
	// コンストラクタ
	SkinningPass();
	// デストラクタ
	virtual ~SkinningPass();

	void SetScene(Engine::SceneManagement::Scene* scene);

	virtual void OnInitialize() override;

	virtual void OnDispatch() override;

};
