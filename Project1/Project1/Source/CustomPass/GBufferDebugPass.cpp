#include "GBufferDebugPass.h"
#include "../Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

static IndexBuffer* index = nullptr;

GBufferDebugPass::GBufferDebugPass()
	: base()
{
	uint32_t i[] =
	{
		0,1,2,3
	};
	index = new IndexBuffer();
	index->SetCount(4);
	index->SetStride(sizeof(uint32_t));
	index->Create(i);
}

GBufferDebugPass::~GBufferDebugPass()
{
}

void GBufferDebugPass::OnInitialize()
{

	ShaderCompiler comp;
	auto vs = comp.Compile(L"Shader/LightingVS.hlsl", L"vs_6_0");
	auto ps = comp.Compile(L"Shader/Debug.hlsl", L"ps_6_0");

	m_pipeline = new RasterizerPipeline();
	m_pipeline->SetVertexShader(vs);
	m_pipeline->SetPixelShader(ps);
	// ラスタライザー設定
	RasterizerDesc rasterizer = RasterizerDesc::Default();
	m_pipeline->SetRasterizerState(rasterizer);

	InputLayoutDesc input = {};
	InputElementDesc elements[] =
	{
		{"POSITION",0,ResourceFormat::RGFloat,0,0,InputClassification::Vertex,0},
		{"TEXCOORD",0,ResourceFormat::RGFloat,1,0,InputClassification::Vertex,0}
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
	root->AddRange(1, ShaderType::Pixel);
	root->AddShaderResourceViewInRanges(0, 0);
	root->AddStaticSamplerState();
	root->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	root->Create();

	m_pipeline->SetRootSignature(root);

	m_pipeline->SetRenderTargetCount(1);
	m_pipeline->SetRenderTargetFormat(ResourceFormat::RGBAUnorm, 0);

	m_pipeline->Create();

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(5);
	m_shaderResourceDescriptor->SetName(L"デスクリプター");

	Rect rect = { -1.0f,1.0f,1.0f,-1.0f };
	m_sprite = Sprite::Create(rect);
}

void GBufferDebugPass::OnRender()
{
	auto pass = ComputePass::Find(L"RaytracingTestPass");
	if (pass)
		pass->Wait();

	auto list = CommandList::Find<GraphicsCommandList>("Graphics");
	auto backBuffer = GetCurrentBackBuffer();

	Resource* resources[] = { backBuffer->GetResource() };

	list->ResourceBarrier(resources, 1, ResourceStates::RenderTarget);

	list->SetGraphicsRootSignature(m_pipeline->GetRootSignature());
	list->SetRasterizerPipeline(m_pipeline);
	list->SetTopology(PrimitiveTopology::TriangleStrip);

	ResourceDescriptor* heaps[] = { m_shaderResourceDescriptor };
	list->SetDescriptorHeaps(heaps, 1);

	Rect rect = { 0.0f,ResolutionWidth,0,ResolutionHeight };
	list->ClearRenderTarget(backBuffer->GetRenderTargetView(), rect);
	list->SetScissorRects(&rect, 1);
	list->SetRenderTargets(&backBuffer, 1, nullptr);

	Viewport viewport[] = { 0.0f,0.0f,ResolutionWidth,ResolutionHeight,0.0f,1.0f };
	list->SetViewports(viewport, 1);

	auto& vertexBuffers = m_sprite->GetVertexBuffers();

	list->SetVertexBuffers(vertexBuffers.data(), 2);

	list->SetIndexBuffer(index);

	list->DrawIndexedInstance(4);

	list->ResourceBarrier(resources, 1, ResourceStates::Present);



}
