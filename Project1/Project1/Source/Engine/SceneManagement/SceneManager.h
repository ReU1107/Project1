#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "../Utility/SingletonObject.h"

namespace Engine
{
	namespace SceneManagement
	{
		class Scene;

		class SceneManager : public SingletonObject<SceneManager>
		{
		private:
			using base = SingletonObject<SceneManager>;
			using ScenePtr = std::shared_ptr<Scene>;
			using Scenes = std::unordered_map<std::string, ScenePtr>;

		private:
			Scenes m_scenes;		// シーン配列
			ScenePtr m_activeScene;	// 稼働中のシーン
		public:
			// コンストラクタ
			SceneManager();
			// デストラクタ
			virtual ~SceneManager();

		public:
			// シーン登録
			void RegisterScene(const std::string& name, ScenePtr scene);

			template<class T>
			void RegisterScene(const std::string& name);

			// シーン検索
			ScenePtr Find(const std::string& name);

			void Start(const std::string& name);

			void Update(float deltaTime);

			void Render();

			void End();

			void Change();

			void SetActiveScene(ScenePtr scene);

			// 稼働中のシーン取得
			ScenePtr GetActiveScene() const;
		};

		template<class T>
		inline void SceneManager::RegisterScene(const std::string& name)
		{
			const auto& it = m_scenes.find(name);
			if (it != m_scenes.cend())
			{
				assert(!"同じ名前のシーンが登録されています");
			}
			auto scene = std::make_shared<T>();
			m_scenes.insert({ name,scene });
		}

	}
}