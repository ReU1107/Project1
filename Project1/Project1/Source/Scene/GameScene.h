#pragma once
#include "../Engine/SceneManagement/Scene.h"

class GameScene : public Engine::SceneManagement::Scene
{
private:
	using base = Engine::SceneManagement::Scene;
public:
	// �R���X�g���N�^
	GameScene();
	// �f�X�g���N�^
	virtual ~GameScene();


	// �����J�n���ɌĂ΂�鏈��
	virtual void OnStart() override;
	// �N�����ɌĂ΂�鏈��
	virtual void OnAwake() override;

	// ���̃V�[���Ŏg�p���郌���_�����O�p�X�o�^
	virtual void OnRegisterRenderingPass() override;

	virtual void OnSetPhysicsScene() override;

};
