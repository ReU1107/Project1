#include "LightingPass.h"
#include "../Engine/Include.h"
#include "../Resolution.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

static IndexBuffer* index = nullptr;

LightingPass::LightingPass()
	: base()
	, m_normal(nullptr)
	, m_albedo(nullptr)
	, m_diffuse(nullptr)
	, m_specular(nullptr)
	, m_depth(nullptr)
	, m_sprite(nullptr)
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

LightingPass::~LightingPass()
{
}

void LightingPass::OnInitialize()
{
	m_normal = Texture::Find<RenderTexture>("法線");
	m_albedo = Texture::Find<RenderTexture>("環境反射係数");
	m_diffuse = Texture::Find<RenderTexture>("拡散反射係数");
	m_specular = Texture::Find<RenderTexture>("鏡面反射係数");
	m_shadow = Texture::Find("レイトレシャドウ結果");
	m_depth = Texture::Find<DepthTexture>("深度");

	ShaderCompiler comp;
	auto vs = comp.Compile(L"Shader/LightingVS.hlsl", L"vs_6_0");
	auto ps = comp.Compile(L"Shader/LightingPS.hlsl", L"ps_6_0", L"Shader/Shading.hlsli");

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
	root->AddRange(6, ShaderType::Pixel);
	root->AddShaderResourceViewInRanges(0, 0);
	root->AddShaderResourceViewInRanges(1, 0);
	root->AddShaderResourceViewInRanges(2, 0);
	root->AddShaderResourceViewInRanges(3, 0);
	root->AddShaderResourceViewInRanges(4, 0);
	root->AddShaderResourceViewInRanges(5, 0);
	//root->AddShaderResourceView(5);
	//root->AddConstantBufferView(0);
	root->AddStaticSamplerState();
	root->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	root->Create();

	m_pipeline->SetRootSignature(root);

	m_pipeline->SetRenderTargetCount(1);
	m_pipeline->SetRenderTargetFormat(ResourceFormat::RGBAUnorm, 0);

	m_pipeline->Create();

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(6);
	m_shaderResourceDescriptor->SetName(L"デスクリプター");

	m_albedo->RecreateShaderResourceView(m_shaderResourceDescriptor);
	m_normal->RecreateShaderResourceView(m_shaderResourceDescriptor);
	m_diffuse->RecreateShaderResourceView(m_shaderResourceDescriptor);
	m_specular->RecreateShaderResourceView(m_shaderResourceDescriptor);
	m_depth->RecreateShaderResourceView(m_shaderResourceDescriptor);
	m_shadow->RecreateShaderResourceView(m_shaderResourceDescriptor);

	Rect rect = { -1.0f,1.0f,1.0f,-1.0f };
	m_sprite = Sprite::Create(rect);

}

void LightingPass::OnRender()
{
	auto computePass = ComputePass::Find(L"RaytracingShadowPass");
	if (computePass)
	{
		computePass->Wait();
	}

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

	list->SetGraphicsDescriptorTable(m_albedo->GetShaderResourceView(), 0);

	auto& vertexBuffers = m_sprite->GetVertexBuffers();

	list->SetVertexBuffers(vertexBuffers.data(), 2);

	list->SetIndexBuffer(index);

	list->DrawIndexedInstance(4);

	list->ResourceBarrier(resources, 1, ResourceStates::Present);

}
