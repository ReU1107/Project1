#include "GameObjectLayer.h"

namespace Engine
{
	GameObjectLayer::GameObjectLayer()
	{
	}
	
	GameObjectLayer::~GameObjectLayer()
	{
	}

	void GameObjectLayer::AddGameObject(GameObjectPtr gameObject)
	{
		m_gameObjects.push_back(gameObject);
	}

	GameObjectLayer::GameObjects& GameObjectLayer::GetGameObjects()
	{
		return m_gameObjects;
	}

}