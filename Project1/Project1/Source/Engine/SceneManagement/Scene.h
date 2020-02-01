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

			// ���ꉞ�����Ă���@�g����ʂ��Ȃ��Ȃ�P�p���܂�
			ComputePasses m_computes;	// Update�p�łȂɂ��R���s���[�g�V�F�[�_�[�ōs���������Ƃ�����Ȃ�g�p����
			mutable bool m_sceneIsDirty;
			mutable bool m_lightIsDirty;
		public:
			// �R���X�g���N�^
			Scene(const std::string& name);
			// �f�X�g���N�^
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

			// �����J�n���ɌĂ΂�鏈��
			virtual void OnStart() {};
			// �N�����ɌĂ΂�鏈��
			virtual void OnAwake() {};

			// �����_�����O�p�X�o�^
			virtual void OnRegisterRenderingPass() {};

			// �������Z���@�ݒ�
			virtual void OnSetPhysicsScene() {};

			// 3D�I�[�f�B�I�ݒ�
			virtual void OnSetAudioScene() {};

			// �V�[���������Ȃ�Ƃ��ɌĂ΂�鏈��
			virtual void OnDestroy() {};

			// �V�[���ύX����Ƃ��ɌĂ΂�鏈��
			virtual void OnChangeScene() {};

		};

	}
}