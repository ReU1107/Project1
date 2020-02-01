#pragma once
#include "GraphicsPass.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace SceneManagement
	{
		class Scene;
	}

	namespace GraphicsSystem
	{
		class RasterizerPipeline;
		class RenderTexture;
		class DepthTexture;
		class ResourceView;
		class ComputePass;
		class ConstantBuffer;

		// �����_�����O�Ɋւ��郏�[�N�t���[�̃p�X
		class RenderingPass : public GraphicsPass
		{
		private:
			using base = GraphicsPass;
			using RenderTexturePtr = std::shared_ptr<RenderTexture>;
			using RenderTargets = std::vector<RenderTexturePtr>;
			using ResourceViews = std::vector<ResourceView*>;
			using ComputePasses = std::vector<ComputePass*>;
		protected:
			ComputePasses m_computePasses;					// ���g�̃p�X�Ƃقړ����ɂ�肽������(�񓯊��R���s���[�g)
			RenderTargets m_renderTargets;					// �����_�[�^�[�Q�b�g�z��
			ResourceViews m_views;							// �r���[�z��
			ResourceDescriptor* m_samplerDescriptor;		// �T���v���[�o�^
			RasterizerPipeline* m_pipeline;					// �p�C�v���C��

			SceneManagement::Scene* m_belongScene;							// �����V�[��
		public:
			// �R���X�g���N�^
			RenderingPass();
			// �f�X�g���N�^
			virtual ~RenderingPass();

			void SetScene(SceneManagement::Scene* scene);

			virtual void OnPreRender();

			virtual void OnRender();

			virtual void OnPostRender();
		};

	}
}