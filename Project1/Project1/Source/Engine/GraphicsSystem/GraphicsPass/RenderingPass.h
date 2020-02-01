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

		// レンダリングに関するワークフローのパス
		class RenderingPass : public GraphicsPass
		{
		private:
			using base = GraphicsPass;
			using RenderTexturePtr = std::shared_ptr<RenderTexture>;
			using RenderTargets = std::vector<RenderTexturePtr>;
			using ResourceViews = std::vector<ResourceView*>;
			using ComputePasses = std::vector<ComputePass*>;
		protected:
			ComputePasses m_computePasses;					// 自身のパスとほぼ同時にやりたいこと(非同期コンピュート)
			RenderTargets m_renderTargets;					// レンダーターゲット配列
			ResourceViews m_views;							// ビュー配列
			ResourceDescriptor* m_samplerDescriptor;		// サンプラー登録
			RasterizerPipeline* m_pipeline;					// パイプライン

			SceneManagement::Scene* m_belongScene;							// 所属シーン
		public:
			// コンストラクタ
			RenderingPass();
			// デストラクタ
			virtual ~RenderingPass();

			void SetScene(SceneManagement::Scene* scene);

			virtual void OnPreRender();

			virtual void OnRender();

			virtual void OnPostRender();
		};

	}
}