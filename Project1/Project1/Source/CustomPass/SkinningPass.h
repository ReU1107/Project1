#pragma once
#include "../Engine/GraphicsSystem/Include.h"

/*
�X�L�j���O���s��
�R���s���[�g�p�X

�X�L�j���O�����̂���Ȃ�
���b�V���̕`�撆�ɔ񓯊��Ŏ��s���Ă���
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
	// �R���X�g���N�^
	SkinningPass();
	// �f�X�g���N�^
	virtual ~SkinningPass();

	void SetScene(Engine::SceneManagement::Scene* scene);

	virtual void OnInitialize() override;

	virtual void OnDispatch() override;

};
