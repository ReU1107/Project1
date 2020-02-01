#pragma once
#include <vector>
#include <array>
#include <memory>
#include <string>

namespace Engine
{
	namespace GraphicsSystem
	{
		class RenderingPass;
		class ComputePass;
		class Mesh;
		class ConstantBuffer;
		class StructuredBuffer;
	}

	namespace PhysicsSystem
	{
		class PhysicsScene;
	}

	namespace AudioSystem
	{
		class AudioScene;
	}

	class GameObject;

	namespace SceneManagement
	{

		class Scene
		{
		private:
			using ComputePasses = std::vector<GraphicsSystem::ComputePass*>;
			using RenderingPasses = std::vector<GraphicsSystem::RenderingPass*>;
			using GameObjectPtr = std::shared_ptr<GameObject>;
			using Objects = std::vector<GameObjectPtr>;
			using StructuredBufferPtr = GraphicsSystem::StructuredBuffer*;
			using StructuredBufferes = std::array<StructuredBufferPtr, 3>;
			using ConstantBufferPtr = GraphicsSystem::ConstantBuffer*;
			using ConstantBuffers = std::array<ConstantBufferPtr, 3>;
			using PhysicsScenePtr = std::shared_ptr<PhysicsSystem::PhysicsScene>;
			using AudioScenePtr = std::shared_ptr<AudioSystem::AudioScene>;

		private:
			std::string m_name;
			ConstantBuffers m_sceneBuffers;
			StructuredBufferes m_lightLists;
			RenderingPasses m_passes;
			Objects m_objects;

			PhysicsScenePtr m_physics;	// 
			AudioScenePtr m_audio;		// 

			// ↓一応おいている　使う場面がないなら撤廃します
			ComputePasses m_computes;	// Update用でなにかコンピュートシェーダーで行いたいことがあるなら使用する
			mutable bool m_sceneIsDirty;
			mutable bool m_lightIsDirty;
		public:
			// コンストラクタ
			Scene(const std::string& name);
			// デストラクタ
			virtual ~Scene();

			void Initialize();

			void AddRenderingPass(GraphicsSystem::RenderingPass* pass);

			void AddObject(std::shared_ptr<GameObject> object);

			Objects& GetObjects() { return m_objects; }

			StructuredBufferPtr GetLightBuffer() const;

			ConstantBufferPtr GetSceneBuffer() const;


			void Update(float deltaTime);

			void PreRender();

			void Render();

			void PostRender();

			bool Traverse(const std::function<bool(GameObjectPtr object)>& func);

			bool TraverseRecurse(GameObjectPtr object, const std::function<bool(GameObjectPtr object)>& func);

			// 処理開始時に呼ばれる処理
			virtual void OnStart() {};
			// 起動時に呼ばれる処理
			virtual void OnAwake() {};

			// レンダリングパス登録
			virtual void OnRegisterRenderingPass() {};

			// 物理演算方法設定
			virtual void OnSetPhysicsScene() {};

			// 3Dオーディオ設定
			virtual void OnSetAudioScene() {};

			// シーンが無くなるときに呼ばれる処理
			virtual void OnDestroy() {};

			// シーン変更するときに呼ばれる処理
			virtual void OnChangeScene() {};

		};

	}
}