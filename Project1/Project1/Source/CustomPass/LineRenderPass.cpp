#include "LineRenderPass.h"
#include "../Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

LineRenderPass::LineRenderPass()
	: base()
{
}

LineRenderPass::~LineRenderPass()
{
}

void LineRenderPass::OnInitialize()
{
	ShaderCompiler com;
	auto vs = com.Compile(L"Shader/LineVS.hlsl", L"vs_6_0");
	auto ps = com.Compile(L"Shader/LinePS.hlsl", L"ps_6_0");

	m_pipeline = new RasterizerPipeline();
	m_pipeline->SetVertexShader(vs);
	m_pipeline->SetPixelShader(ps);
	m_pipeline->SetBlendState(BlendDesc::NoBlend());
	InputElementDesc elements[] = {
		{"POSITION",0,ResourceFormat::RGBFloat,0,0,InputClassification::Vertex,0 },
		{"COLOR",0,ResourceFormat::RGBAFloat,0,12,InputClassification::Vertex,0 }
	};
	InputLayoutDesc inputLayout = {};
	inputLayout.elements = elements;
	inputLayout.elementCount = 2;
	m_pipeline->SetInputLayout(inputLayout);

	m_pipeline->SetRenderTargetCount(1);
	m_pipeline->SetRenderTargetFormat(ResourceFormat::RGBAUnorm, 0);

	DepthStencilDesc depthStencil = {};
	depthStencil.depthEnable = false;
	depthStencil.stencilEnable = false;
	m_pipeline->SetDepthStencilState(depthStencil);
	m_pipeline->SetRasterizerState(RasterizerDesc::Default());

	RootSignature* rootSignature = new RootSignature();
	rootSignature->AddConstantBufferView(0, 0, ShaderType::Vertex);
	rootSignature->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	rootSignature->Create();

	m_pipeline->SetRootSignature(rootSignature);

	m_pipeline->Create();

}

void LineRenderPass::OnRender()
{
	auto list = CommandList::Find<GraphicsCommandList>("Graphics");

	auto backBuffer = GetCurrentBackBuffer();

	Resource* resources[] = { backBuffer->GetResource() };

	list->ResourceBarrier(resources, 1, ResourceStates::RenderTarget);

	list->SetGraphicsRootSignature(m_pipeline->GetRootSignature());
	list->SetRasterizerPipeline(m_pipeline);

	list->SetTopology(PrimitiveTopology::TriangleList);

	Rect rect = { 0.0f,ResolutionWidth,0,ResolutionHeight };
	//list->ClearRenderTarget(backBuffer->GetRenderTargetView(), rect, Color4::Blue);
	list->SetScissorRects(&rect, 1);
	list->SetRenderTargets(&backBuffer, 1, nullptr);

	Viewport viewport[] = { 0.0f,0.0f,ResolutionWidth,ResolutionHeight,0.0f,1.0f };
	list->SetViewports(viewport, 1);

	auto camera = Camera::main;

	list->SetGraphicsConstantBuffer(camera->GetConstantBuffer(), 0);

	auto objects = m_belongScene->GetObjects();

	for (auto& object : objects)
	{
		auto renderer = object->GetComponent<LineRenderer>();
		if (renderer)
		{
			uint32_t indexCount = renderer->GetUseIndexCount();
			auto vertexBuffer = renderer->GetVertexBuffer();
			auto indexBuffer = renderer->GetIndexBuffer();

			list->SetVertexBuffers(&vertexBuffer, 1);

			list->SetIndexBuffer(indexBuffer);

			list->DrawIndexedInstance(indexCount);
		}

	}

	list->ResourceBarrier(resources, 1, ResourceStates::Present);

}
