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
			Scenes m_scenes;		// �V�[���z��
			ScenePtr m_activeScene;	// �ғ����̃V�[��
		public:
			// �R���X�g���N�^
			SceneManager();
			// �f�X�g���N�^
			virtual ~SceneManager();

		public:
			// �V�[���o�^
			void RegisterScene(const std::string& name, ScenePtr scene);

			template<class T>
			void RegisterScene(const std::string& name);

			// �V�[������
			ScenePtr Find(const std::string& name);

			void Start(const std::string& name);

			void Update(float deltaTime);

			void Render();

			void End();

			void Change();

			void SetActiveScene(ScenePtr scene);

			// �ғ����̃V�[���擾
			ScenePtr GetActiveScene() const;
		};

		template<class T>
		inline void SceneManager::RegisterScene(const std::string& name)
		{
			const auto& it = m_scenes.find(name);
			if (it != m_scenes.cend())
			{
				assert(!"�������O�̃V�[�����o�^����Ă��܂�");
			}
			auto scene = std::make_shared<T>();
			m_scenes.insert({ name,scene });
		}

	}
}