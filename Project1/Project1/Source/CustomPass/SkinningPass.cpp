#include "SkinningPass.h"
#include "../Engine/Include.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

SkinningPass::SkinningPass()
	: base()
	, m_belongScene(nullptr)
{
}

SkinningPass::~SkinningPass()
{
}

void SkinningPass::SetScene(Engine::SceneManagement::Scene* scene)
{
	m_belongScene = scene;
}

void SkinningPass::OnInitialize()
{
	Register(L"SkinningPass", this);

	ShaderCompiler compiler;
	auto cs = compiler.Compile(L"Shader/SkinnedMorphCS.hlsl", L"cs_6_0");

	RootSignature* rootSignature = new RootSignature();
	rootSignature->AddRange(5);
	rootSignature->AddUnorderedAccessViewInRanges(0, 0);
	rootSignature->AddShaderResourceViewInRanges(0, 0);
	rootSignature->AddShaderResourceViewInRanges(1, 0);
	rootSignature->AddShaderResourceViewInRanges(2, 0);
	rootSignature->AddConstantBufferViewInRanges(0, 0);
	rootSignature->Create();

	m_pipeline = new ComputePipeline();
	m_pipeline->SetRootSignature(rootSignature);
	m_pipeline->SetComputeShader(cs);

	m_pipeline->Create();

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(100);

}

void SkinningPass::OnDispatch()
{
	Start();

	auto list = CommandList::Find<GraphicsCommandList>("Graphics3");
	auto queue = CommandQueue::Find<GraphicsCommandQueue>("Graphics3");

	auto objects = m_belongScene->GetObjects();

	m_shaderResourceDescriptor->Reset();

	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	list->SetComputePipeline(m_pipeline);

	list->SetComputeRootSignature(m_pipeline->GetRootSignature());

	for (auto& renderer : SkinnedMeshRenderer::allSkinnedMeshRenderers)
	{
		if (!renderer->IsView())
			continue;

		renderer->CalculateBlendShape();
		auto mesh = renderer->GetMesh();
		mesh->Update();
		auto vertexBuffers = mesh->GetVertexBuffers();
		auto paletteBuffer = renderer->GetMatrixPaletteBuffer();

		Buffer* buffers[7] = {};
		uint32_t index = 0;
		for (auto& vertexBuffer : vertexBuffers)
		{
			buffers[index++] = vertexBuffer;
		}

		buffers[index++] = paletteBuffer;

		list->ResourceBarrier(buffers, index, ResourceStates::CopyDestination);

		for (uint32_t i = 0; i < index; ++i)
		{
			list->CopyBuffer(buffers[i]);
		}

		list->ResourceBarrier(buffers, index, ResourceStates::GenericRead);

		auto positionBuffer = mesh->GetVertexBuffer(VertexLayout::Positions);
		auto baseBuffer = mesh->GetVertexBuffer(VertexLayout::BasePositions);
		auto deltaBuffer = mesh->GetVertexBuffer(VertexLayout::DeltaPositions);
		auto boneBuffer = mesh->GetVertexBuffer(VertexLayout::BoneWeights);

		positionBuffer->RecreateResourceView(m_shaderResourceDescriptor);
		baseBuffer->RecreateResourceView(m_shaderResourceDescriptor);
		deltaBuffer->RecreateResourceView(m_shaderResourceDescriptor);
		boneBuffer->RecreateResourceView(m_shaderResourceDescriptor);
		paletteBuffer->RecreateResourceView(m_shaderResourceDescriptor);

		list->SetComputeDescriptorTable(m_shaderResourceDescriptor, 0);

		auto count = mesh->GetVertexCount();

		list->DispatchCompute(count / 128, 1, 1);

		list->UnorderedAccessBarrier(buffers, index);

	}
	
	queue->ExecuteCommandLists(&list, 1);

	queue->WaitExecutionList();

	list->Reset();

	End();
}
