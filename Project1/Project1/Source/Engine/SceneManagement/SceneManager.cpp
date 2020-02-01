#include "SceneManager.h"
#include "Scene.h"

namespace Engine
{
	namespace SceneManagement
	{
		SceneManager::SceneManager()
			: base()
			, m_scenes()
			, m_activeScene(nullptr)
		{
		}
		
		SceneManager::~SceneManager()
		{
			m_scenes.clear();
		}

		void SceneManager::RegisterScene(const std::string& name, ScenePtr scene)
		{
			const auto& it = m_scenes.find(name);
			if (it != m_scenes.cend())
			{
				assert(!"“¯‚¶–¼‘O‚ÌƒV[ƒ“‚ª“o˜^‚³‚ê‚Ä‚¢‚Ü‚·");
			}
			m_scenes.insert({ name,scene });
		}

		SceneManager::ScenePtr SceneManager::Find(const std::string& name)
		{
			const auto& it = m_scenes.find(name);
			if (it == m_scenes.cend())
			{
				return nullptr;
			}
			return (*it).second;
		}

		void SceneManager::Start(const std::string& name)
		{
			m_activeScene = Find(name);
			m_activeScene->Initialize();
		}

		void SceneManager::Update(float deltaTime)
		{
			m_activeScene->Update(deltaTime);
		}

		void SceneManager::Render()
		{
			m_activeScene->Render();
		}

		void SceneManager::End()
		{
			m_activeScene;
		}

		void SceneManager::Change()
		{
			m_activeScene->OnChangeScene();
		}

		void SceneManager::SetActiveScene(ScenePtr scene)
		{
			m_activeScene = scene;
		}

		SceneManager::ScenePtr SceneManager::GetActiveScene() const
		{
			return m_activeScene;
		}
	}
}