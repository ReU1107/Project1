#include "MeshRenderer.h"
#include "../Filter/MeshFilter.h"
#include "../../../ModelData.h"
#include "../Transform.h"
#include "../../../GraphicsSystem/Include.h"

namespace Engine
{
	using namespace GraphicsSystem;

	std::vector<MeshRenderer::MeshRendererPtr> MeshRenderer::allMeshRenderers;

	MeshRenderer::MeshRenderer() noexcept
		: base("MeshRenderer")
		, m_mesh(nullptr)
		, m_constantBuffer(nullptr)
	{
		SetShadowCastingMode(ShadowCastingMode::On);
		m_constantBuffer = new ConstantBuffer();
		m_constantBuffer->SetStride(sizeof(ModelData));
		m_constantBuffer->SetCount(1);
		m_constantBuffer->Create();
	}

	MeshRenderer::~MeshRenderer() noexcept
	{
		delete m_constantBuffer;
	}

	void MeshRenderer::SetMesh(MeshPtr mesh)
	{
		m_mesh = mesh;
	}

	MeshRenderer::MeshPtr MeshRenderer::GetMesh() const
	{
		return m_mesh;
	}

	MeshRenderer::ConstantBufferPtr MeshRenderer::GetConstantBuffer() const
	{
		ModelData data = {};
		data.worldMatrix = GetTransform()->GetLocalToWorld();

		m_constantBuffer->Update(&data);
		return m_constantBuffer;
	}

}
