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
		GameObjects m_gameObjects;	// グループ内のゲームオブジェクト配列

	public:
		// コンストラクタ
		GameObjectLayer();
		// デストラクタ
		~GameObjectLayer();

	public:
		// ゲームオブジェクト追加
		void AddGameObject(GameObjectPtr gameObject);

		GameObjects& GetGameObjects();
	};
}