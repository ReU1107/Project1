#pragma once
#include <iostream>
#include <vector>

namespace Engine
{
	class GameObject;

	class GameObjectLayer
	{
	private:
		using GameObjectPtr = std::shared_ptr<GameObject>;
		using GameObjects = std::vector<GameObjectPtr>;
	private:
		GameObjects m_gameObjects;	// �O���[�v���̃Q�[���I�u�W�F�N�g�z��

	public:
		// �R���X�g���N�^
		GameObjectLayer();
		// �f�X�g���N�^
		~GameObjectLayer();

	public:
		// �Q�[���I�u�W�F�N�g�ǉ�
		void AddGameObject(GameObjectPtr gameObject);

		GameObjects& GetGameObjects();
	};
}