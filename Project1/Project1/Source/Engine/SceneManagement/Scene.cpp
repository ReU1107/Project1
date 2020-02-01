#include "Scene.h"
#include "../GraphicsSystem/Include.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Component/Include.h"
#include "../LightData.h"
#include "../PhysicsSystem/PhysicsScene.h"
#include "../AudioSystem/AudioScene.h"
#include "../Utility/Timer.h"

namespace Engine
{
	using namespace Engine::GraphicsSystem;
	using namespace Engine::PhysicsSystem;
	namespace SceneManagement
	{
		struct SceneData
		{
			uint32_t lightCount;
			float refraction;
		};

		static const uint32_t LightMaxCount = 50;

		Scene::Scene(const std::string& name)
			: m_name(name)
			, m_physics(nullptr)
			, m_audio(nullptr)
			, m_sceneIsDirty(true)
			, m_lightIsDirty(true)
		{

			for (uint32_t i = 0; i < 3; ++i)
			{
				m_sceneBuffers[i] = new ConstantBuffer();
				m_sceneBuffers[i]->SetStride(sizeof(SceneData));
				m_sceneBuffers[i]->SetCount(1);
				m_sceneBuffers[i]->Create();

				m_lightLists[i] = new StructuredBuffer();
				m_lightLists[i]->SetStride(sizeof(LightData));
				m_lightLists[i]->Dynamic(false);
				m_lightLists[i]->Raw(false);
				m_lightLists[i]->SetCount(LightMaxCount);
				m_lightLists[i]->SetFlags(ResourceFlags::AllowUnorderedAccess);
				m_lightLists[i]->Create();
			}

			m_physics = std::make_shared<PhysicsScene>(BloadPhaseType::AABBTree);
		}

		Scene::~Scene()
		{
			for (auto& pass : m_passes)
			{
				delete pass;
			}
			for (auto& buffer : m_sceneBuffers)
			{
				delete buffer;
			}
			for (auto& list : m_lightLists)
			{
				delete list;
			}
		}

		void Scene::Initialize()
		{
			Traverse(
				[](GameObjectPtr object)->bool
				{
					object->Start();
					return true;
				}
			);

			for (auto& pass : m_passes)
			{
				pass->OnInitialize();
			}
		}

		void Scene::AddRenderingPass(GraphicsSystem::RenderingPass* pass)
		{
			pass->SetScene(this);
			m_passes.push_back(pass);
		}

		void Scene::AddObject(std::shared_ptr<GameObject> object)
		{
			m_objects.push_back(object);
		}

		Scene::StructuredBufferPtr Scene::GetLightBuffer() const
		{
			auto lightBuffer = m_lightLists[GetCurrentIndex()];
			if (m_lightIsDirty)
			{
				LightData lightData[LightMaxCount] = {};
				uint32_t index = 0;
				for (auto& light : Light::allLights)
				{
					auto& data = lightData[index];
					data.color = light->GetColor();
					data.position = light->GetPosition();
					data.direction = light->GetDirection();
					data.range = light->GetFarRange();
					data.type = (uint32_t)light->GetType();
					index++;
				}
				lightBuffer->Update(lightData);
				m_lightIsDirty = false;
			}
			return lightBuffer;
		}

		Scene::ConstantBufferPtr Scene::GetSceneBuffer() const
		{
			auto sceneBuffer = m_sceneBuffers[GetCurrentIndex()];

			if (m_sceneIsDirty)
			{
				SceneData data = {};
				data.lightCount = Light::allLigthsCount;
				data.refraction = 1.0f;
				sceneBuffer->Update(&data);
				m_sceneIsDirty = false;
			}
			return sceneBuffer;
		}

		void Scene::Update(float deltaTime)
		{
			// ゲームオブジェクトを更新する
			Traverse(
				[&](GameObjectPtr object)->bool
				{
					object->Update(deltaTime);
					return true;
				}
			);

			// アニメーションを更新する
			for (auto& animator : Animator::allAnimators)
			{
				animator->Update(deltaTime);
			}

			Traverse(
				[&](GameObjectPtr object)->bool
				{
					object->LateUpdate(deltaTime);
					return true;
				}
			);


		/*	if (m_physics)
				m_physics->Simulate(deltaTime);

			if (m_audio)
				m_audio->Simulate(deltaTime);*/

			m_lightIsDirty = true;
			m_sceneIsDirty = true;
		}

		void Scene::PreRender()
		{
			// カリング等を行う

			for (auto& pass : m_passes)
			{
				pass->OnPreRender();
			}
		}

		void Scene::Render()
		{
			// ライトの情報をバッファに入れる
			// ライトのカリングを大なうべき？

			for (auto& camera : Camera::allCameras)
			{
				Camera::current = camera;
				for (auto& pass : m_passes)
				{
					pass->OnRender();
				}
			}
		}

		void Scene::PostRender()
		{
			for (auto& pass : m_passes)
			{
				pass->OnPostRender();
			}
		}
		
		bool Scene::Traverse(const std::function<bool(GameObjectPtr object)>& func)
		{
			uint32_t count = m_objects.size();
			for (uint32_t i = 0; i < count; ++i)
			{
				TraverseRecurse(m_objects[i], func);
			}
			return false;
		}

		bool Scene::TraverseRecurse(GameObjectPtr object, const std::function<bool(GameObjectPtr object)>& func)
		{
			if (!func(object))
				return false;

			auto sibling = object->GetNextSibling();
			if (sibling)
			{
				TraverseRecurse(sibling, func);
			}

			auto child = object->GetOldestChild();
			if (child)
			{
				TraverseRecurse(child, func);
			}

			return true;
		}
	}
}