#include "PreZPass.h"
#include "..//Engine/Include.h"
#include "../Resolution.h"
#include "../Engine/CameraData.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

PreZPass::PreZPass()
	: base()
{
}

PreZPass::~PreZPass()
{
}

void PreZPass::OnInitialize()
{
	auto depthTexture = DepthTexture::Create("PreZ", 1280, 960, ResourceFormat::Depth16);
	m_pipeline = new RasterizerPipeline();
	m_pipeline->SetDepthStencilFormat(depthTexture->GetFormat());
	m_pipeline->SetRenderTargetCount(0);
	ShaderCompiler com;
	auto vShader = com.Compile(L"Shader/PreZVS.hlsl", L"vs_6_0", L"Shader/PreZHeader.hlsli");
	auto pShader = com.Compile(L"Shader/PreZPS.hlsl", L"ps_6_0", L"Shader/PreZHeader.hlsli");
	m_pipeline->SetVertexShader(vShader);
	m_pipeline->SetPixelShader(pShader);

	RootSignature* root = new RootSignature();
	root->AddConstantBufferView(0, 0, ShaderType::Vertex);
	root->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	root->Create();

	m_pipeline->SetRootSignature(root);

	// ラスタライザー設定
	RasterizerDesc rasterizer = RasterizerDesc::Default();
	m_pipeline->SetRasterizerState(rasterizer);

	InputLayoutDesc input = {};
	InputElementDesc elements[] =
	{
		{"POSITION",0,ResourceFormat::RGBFloat,0,0,InputClassification::Vertex,0},
	};
	input.elements = elements;
	input.elementCount = 1;
	m_pipeline->SetInputLayout(input);

	m_pipeline->Create();
}

void PreZPass::OnRender()
{
	// メッシュ配列をゲームオブジェクトに変更します
	auto objects = m_belongScene->GetObjects();

	auto list = CommandList::Find<GraphicsCommandList>("Graphics");
	auto queue = CommandQueue::Find<GraphicsCommandQueue>("Graphics");

	Rect rect = { 0.0f,ResolutionWidth,0,ResolutionHeight };

	auto depth = Texture::Find<DepthTexture>("PreZ");
	list->ClearDepthStencil(depth->GetDepthStencilView(), rect);

	list->SetGraphicsRootSignature(m_pipeline->GetRootSignature());
	list->SetRasterizerPipeline(m_pipeline);

	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	list->SetTopology(PrimitiveTopology::TriangleList);

	Viewport viewport[] = { 0.0f,0.0f,ResolutionWidth,ResolutionHeight,0.0f,1.0f };
	list->SetViewports(viewport, 1);
	list->SetScissorRects(&rect, 1);

	auto camera = Camera::current;

	list->SetGraphicsConstantBuffer(camera->GetConstantBuffer(), 0);
	for (uint32_t i = 0; i < objects.size(); ++i)
	{
		auto object = objects[i];
		auto renderer = object->GetComponent<MeshRenderer>();

		if (renderer)
		{
			auto mesh = renderer->GetMesh();
			if (mesh)
			{

				list->SetGraphicsConstantBuffer(renderer->GetConstantBuffer(), 1);

				auto& vertexBuffers = mesh->GetVertexBuffers();
				list->SetVertexBuffers(vertexBuffers.data(), 1);

				for (auto& subMesh : mesh->GetSubMeshes())
				{
					auto* indexBuffer = subMesh->GetIndexBuffer();
					list->SetIndexBuffer(indexBuffer);

					uint32_t count = subMesh->GetUseIndexCount();
					list->DrawIndexedInstance(count);
				}
			}
		}
	}
	std::shared_ptr<GraphicsCommandList> lists[] = { list };
	queue->ExecuteCommandLists(lists, 1);

	queue->WaitExecutionList();

	list->Reset();

}
