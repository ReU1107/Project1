#include "RenderingPass.h"
#include <cassert>
#include "RasterizerPipeline.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		RenderingPass::RenderingPass()
			: base()
			, m_samplerDescriptor(nullptr)
			, m_pipeline(nullptr)
			, m_belongScene(nullptr)
		{
		}

		RenderingPass::~RenderingPass()
		{
			delete m_pipeline;
			delete m_samplerDescriptor;
		}

		void RenderingPass::SetScene(SceneManagement::Scene* scene)
		{
			m_belongScene = scene;
		}

		void RenderingPass::OnPreRender()
		{
		}

		void RenderingPass::OnRender()
		{
		}
		
		void RenderingPass::OnPostRender()
		{
		}
	}
}