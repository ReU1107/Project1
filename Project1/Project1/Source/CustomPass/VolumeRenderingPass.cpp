#include "VolumeRenderingPass.h"
#include "..//Engine/Include.h"

using namespace Engine;
using namespace Engine::GraphicsSystem;

VolumeRenderingPass::VolumeRenderingPass()
	: base()
	, m_result(nullptr)
	, m_sceneBuffer(nullptr)
{
	//ComputePass::Register(L"VolumeRenderingPass", this);
}

VolumeRenderingPass::~VolumeRenderingPass()
{
	delete m_sceneBuffer;
}

void VolumeRenderingPass::OnInitialize()
{
	ShaderCompiler compiler;
	auto shader = compiler.Compile(L"Shader/ComputeShader.hlsl", L"cs_6_0");

	RootSignature* rootSignature = new RootSignature();
	rootSignature->AddRange(1);
	rootSignature->AddUnorderedAccessViewInRanges(0, 0);
	//rootSignature->AddConstantBufferView(0);
	rootSignature->Create();
	m_pipeline = new ComputePipeline();

	m_pipeline->SetComputeShader(shader);
	m_pipeline->SetRootSignature(rootSignature);

	m_pipeline->Create();

	m_shaderResourceDescriptor = ResourceDescriptor::CreateShaderResource(1);

	m_sceneBuffer = new ConstantBuffer();
	m_sceneBuffer->SetStride(sizeof(DirectX::XMFLOAT3));
	m_sceneBuffer->SetCount(1);
	m_sceneBuffer->SetFlags(ResourceFlags::AllowUnorderedAccess);
	m_sceneBuffer->Create();

	m_result = Texture::Create("Result", 1280, 960, ResourceFormat::RGBAUnorm, false, false, true);
	m_result->SetName(L"結果受け取り用テクスチャ");

	m_result->CreateUnorderedAccessView();
}

void VolumeRenderingPass::OnDispatch()
{
	auto list = CommandList::Find<GraphicsCommandList>("Graphics");
	auto queue = CommandQueue::Find<GraphicsCommandQueue>("Graphics");

	auto backBuffer = GetCurrentBackBuffer();
	Resource* resources[] = { backBuffer->GetResource(),m_result->GetResource() };

	list->ResourceBarrier(&resources[1], 1, ResourceStates::UnorderedAccess);

	list->SetComputeRootSignature(m_pipeline->GetRootSignature());
	list->SetComputePipeline(m_pipeline);
	list->SetDescriptorHeaps(&m_shaderResourceDescriptor, 1);

	//list->SetComputeConstantBuffer(m_sceneBuffer, 0);
	list->SetComputeDescriptorTable(m_result->GetUnorderedAccessView(), 0);

	list->DispatchCompute(40, 40, 1);
	// 全て最低限1にする必要がある
	//list->DispatchCompute(1, 1, 1);

	list->UnorderedAccessBarrier(&resources[1], 1);

	list->ResourceBarrier(&resources[1], 1, ResourceStates::CopySource);

	list->ResourceBarrier(&resources[0], 1, ResourceStates::CopyDestination);

	list->CopyResource(resources[1], resources[0]);

	list->ResourceBarrier(&resources[0], 1, ResourceStates::Present);

	std::shared_ptr<GraphicsCommandList> lists[] = { list };
	queue->ExecuteCommandLists(lists, 1);

	queue->WaitExecutionList();

	list->Reset();

}
