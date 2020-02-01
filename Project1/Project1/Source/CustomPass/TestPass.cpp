#include "TestPass.h"
#include "../Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

static IndexBuffer* index = nullptr;
static VertexBuffer* vertex = nullptr;

TestPass::TestPass()
	: base()
{
	uint32_t i[] =
	{
		0,1,2
	};
	index = new IndexBuffer();
	index->SetCount(3);
	index->SetStride(sizeof(uint32_t));
	index->Create(i);
}

TestPass::~TestPass()
{
}

void TestPass::OnInitialize()
{
	ShaderCompiler comp;
	auto vs = comp.Compile(L"Shader/LineVS.hlsl", L"vs_6_0");
	auto ps = comp.Compile(L"Shader/LinePS.hlsl", L"ps_6_0");

	m_pipeline = new RasterizerPipeline();
	m_pipeline->SetVertexShader(vs);
	m_pipeline->SetPixelShader(ps);
	// ラスタライザー設定
	RasterizerDesc rasterizer = RasterizerDesc::Default();
	m_pipeline->SetRasterizerState(rasterizer);

	InputLayoutDesc input = {};
	InputElementDesc elements[] =
	{
		{"POSITION",0,ResourceFormat::RGBFloat,0,0,InputClassification::Vertex,0},
		{"COLOR",0,ResourceFormat::RGBAFloat,0,12,InputClassification::Vertex,0}
	};
	input.elements = elements;
	input.elementCount = 2;
	m_pipeline->SetInputLayout(input);
	// ブレンドステート設定
	BlendDesc blend = {};
	blend.alphaToCoverageEnable = false;
	blend.independentBlendEnable = false;
	blend.renderTargets[0] = RenderTargetBlendDesc::Default();
	m_pipeline->SetBlendState(blend);

	// デプスステンシル設定
	DepthStencilDesc depthStencilDesc = {};
	depthStencilDesc.depthEnable = false;
	depthStencilDesc.stencilEnable = false;
	m_pipeline->SetDepthStencilState(depthStencilDesc);
	// ルートシグネチャ設定
	RootSignature* root = new RootSignature();
	root->AddConstantBufferView(0, 0, ShaderType::Vertex);
	root->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	root->Create();

	m_pipeline->SetRootSignature(root);

	m_pipeline->SetRenderTargetCount(1);
	m_pipeline->SetRenderTargetFormat(ResourceFormat::RGBAUnorm, 0);

	m_pipeline->Create();

	vertex = new VertexBuffer();
	vertex->SetCount(3);
	vertex->SetStride(sizeof(LineVertex3D));

	LineVertex3D vertices[] =
	{
		{Vector3(0,100,0),Color4(),},
		{Vector3(100,0,0),Color4(),},
		{Vector3(-100,0,0),Color4(),}
	};

	vertex->Create(vertices);
}

void TestPass::OnRender()
{
	auto list = CommandList::Find<GraphicsCommandList>("Graphics");

	auto backBuffer = GetCurrentBackBuffer();

	Resource* resources[] = { backBuffer->GetResource() };

	list->ResourceBarrier(resources, 1, ResourceStates::RenderTarget);

	list->SetGraphicsRootSignature(m_pipeline->GetRootSignature());
	list->SetRasterizerPipeline(m_pipeline);

	list->SetTopology(PrimitiveTopology::TriangleStrip);

	Rect rect = { 0.0f,ResolutionWidth,0,ResolutionHeight };
	//list->ClearRenderTarget(backBuffer->GetRenderTargetView(), rect);
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

	//list->SetVertexBuffers(&vertex, 1);

	//list->SetIndexBuffer(index);

	//list->DrawIndexedInstance(3);

	list->ResourceBarrier(resources, 1, ResourceStates::Present);

}
