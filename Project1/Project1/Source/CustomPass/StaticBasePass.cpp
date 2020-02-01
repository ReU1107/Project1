#include "StaticBasePass.h"
#include "..//Engine/Include.h"
#include "../Resolution.h"
#include "SkinningPass.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;
using namespace Engine::ThreadSystem;

StaticBasePass::StaticBasePass()
	: base()
	, m_depth(nullptr)
{
}

StaticBasePass::~StaticBasePass()
{
}

void StaticBasePass::OnInitialize()
{
	m_depth = DepthTexture::Create("深度", 1280, 960, ResourceFormat::Depth32);

	m_renderTargets.resize(4);
	m_renderTargets[0] = RenderTexture::Create("環境反射係数", 1280, 960, ResourceFormat::RGB10A2Unorm, false);
	m_renderTargets[1] = RenderTexture::Create("法線", 1280, 960, ResourceFormat::RGBAFloat, false);
	m_renderTargets[2] = RenderTexture::Create("拡散反射係数", 1280, 960, ResourceFormat::RGB10A2Unorm, false);
	m_renderTargets[3] = RenderTexture::Create("鏡面反射係数", 1280, 960, ResourceFormat::RGBAFloat, false);

	ShaderCompiler comp;
	auto vs = comp.Compile(L"Shader/MeshVS.hlsl", L"vs_6_0", L"Shader/MeshHeader.hlsli");
	auto ps = comp.Compile(L"Shader/GBufferPS.hlsl", L"ps_6_0", L"Shader/MeshHeader.hlsli");

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
		{"NORMAL",0,ResourceFormat::RGBFloat,1,0,InputClassification::Vertex,0},
		{"TEXCOORD",0,ResourceFormat::RGFloat,2,0,InputClassification::Vertex,0}
	};
	input.elements = elements;
	input.elementCount = ARRAYSIZE(elements);
	m_pipeline->SetInputLayout(input);
	// ブレンドステート設定
	BlendDesc blend = {};
	blend.alphaToCoverageEnable = false;
	blend.independentBlendEnable = false;
	blend.renderTargets[0] = RenderTargetBlendDesc::Default();
	m_pipeline->SetBlendState(blend);

	// デプスステンシル設定
	DepthStencilDesc depthStencilDesc = DepthStencilDesc::Default();
	m_pipeline->SetDepthStencilState(depthStencilDesc);
	// ルートシグネチャ設定
	RootSignature* root = new RootSignature();
	root->AddConstantBufferView(0, 0, ShaderType::Vertex);
	root->AddConstantBufferView(1, 0, ShaderType::Vertex);
	root->AddConstantBufferView(0, 0, ShaderType::Pixel);
	root->AddRange(1, ShaderType::Pixel);
	root->AddShaderResourceViewInRanges(0, 0);
	root->AddStaticSamplerState();
	root->SetFlags(RootSignatureFlags::AllowInputAssemblerInputLayout);
	root->Create();

	m_pipeline->SetRootSignature(root);

	m_pipeline->SetDepthStencilFormat(ResourceFormat::Depth32);
	m_pipeline->SetRenderTargetCount(4);
	for (uint32_t i = 0; i < 4; ++i)
	{
		m_pipeline->SetRenderTargetFormat(m_renderTargets[i]->GetFormat(), i);
	}

	m_pipeline->Create();

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(100);
	m_shaderResourceDescriptor->SetName(L"BasePassシェーダーリソースヒープ");

	SkinningPass* pass = new SkinningPass();
	pass->OnInitialize();
	pass->SetScene(m_belongScene);

	m_computePasses.resize(1);
	m_computePasses[0] = pass;

}

void StaticBasePass::OnRender()
{
	SingleRequestManager::GetPtr()->PushRequest((SkinningPass*)m_computePasses[0], &SkinningPass::OnDispatch);

	DBGSTR(" ====== A3 \n");

	// メッシュ配列をゲームオブジェクトに変更します
	auto camera = Camera::current;
	auto objects = m_belongScene->GetObjects();

	auto list = CommandList::Find<GraphicsCommandList>("Graphics");

	Resource* resources[] = {
		m_renderTargets[0]->GetResource(),m_renderTargets[1]->GetResource(),
		m_renderTargets[2]->GetResource(),m_renderTargets[3]->GetResource() };

	list->ResourceBarrier(resources, 4, ResourceStates::RenderTarget);
	Rect rect = { 0.0f,ResolutionWidth,0,ResolutionHeight };

	for (auto& renderTarget : m_renderTargets)
	{
		list->ClearRenderTarget(renderTarget->GetRenderTargetView(), rect, Color4::Black);
	}

	list->ClearDepthStencil(m_depth->GetDepthStencilView(), rect);

	list->SetRenderTargets(m_renderTargets.data(), 4, m_depth);

	list->SetGraphicsRootSignature(m_pipeline->GetRootSignature());
	list->SetRasterizerPipeline(m_pipeline);

	m_shaderResourceDescriptor->Reset();

	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	list->SetTopology(PrimitiveTopology::TriangleList);

	Viewport viewport[] = { 0.0f,0.0f,ResolutionWidth,ResolutionHeight,0.0f,1.0f };
	list->SetViewports(viewport, 1);
	list->SetScissorRects(&rect, 1);

	list->SetGraphicsConstantBuffer(camera->GetConstantBuffer(), 0);

	DBGSTR(" ====== B3 \n");

	for (auto& renderer : MeshRenderer::allMeshRenderers)
	{
		if (!renderer->IsView())
			continue;

		auto mesh = renderer->GetMesh();
		if (mesh)
		{
			auto buffer = renderer->GetConstantBuffer();

			list->SetGraphicsConstantBuffer(buffer, 1);

			auto& vertexBuffers = mesh->GetVertexBuffers();
			list->SetVertexBuffers(vertexBuffers.data(), vertexBuffers.size());

			for (auto& subMesh : mesh->GetSubMeshes())
			{
				auto* indexBuffer = subMesh->GetIndexBuffer();
				list->SetIndexBuffer(indexBuffer);

				auto material = subMesh->GetMaterial();
				// 定数バッファ、テクスチャ設定
				ConstantBuffer* constantBuffer = material->GetConstantBuffer();
				if (constantBuffer)
				{
					list->SetGraphicsConstantBuffer(constantBuffer, 2);
				}
				auto texture = material->GetDecalTexture();
				if (texture)
				{
					texture->RecreateShaderResourceView(m_shaderResourceDescriptor);
					list->SetGraphicsDescriptorTable(texture->GetShaderResourceView(), 3);
				}

				uint32_t count = subMesh->GetUseIndexCount();
				list->DrawIndexedInstance(count);
			}
		}
	}
	list->ResourceBarrier(resources, 4, ResourceStates::PixelShaderResource);
	DBGSTR(" ====== C3 \n");

}
