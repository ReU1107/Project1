#pragma once
#include "..//Interface/ICommandList.h"
struct ID3D12GraphicsCommandList5;
struct ID3D12CommandAllocator;

namespace Engine
{
	namespace GraphicsSystem 
	{
		class D3D12CommandList final : public ICommandList
		{
		public:
			ID3D12GraphicsCommandList5* m_nativeList;
			ID3D12CommandAllocator* m_nativeAllocator;

		public:
			// �R���X�g���N�^
			D3D12CommandList();
			// �f�X�g���N�^
			virtual ~D3D12CommandList();
			// 
			virtual void* GetNativeCommandList() const override;

			virtual void ClearRenderTarget(IResourceView* renderTargetView, const Rect& rect, float color[4]) const override;

			virtual void ClearDepthStencil(IResourceView* depthStencilView, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const override;

			virtual void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) const override;

			virtual void BuildBottomLevelAccelerationStructure(IAccelerationStructure* as) const override;

			// �V�[���쐬�R�}���h���s
			virtual void BuildTopLevelAccelerationStructure(IAccelerationStructure* as) const override;

			// ���C�g���[�V���O���s�R�}���h���s
			virtual void DispatchRaytracing(const RaytracingDispatchDesc& desc) const override;
			// ���\�[�X�̎d�l���@��ύX���Ӑ}���Ȃ��A�N�Z�X��h���܂�
			virtual void ResourceBarrierTransition(IResource* resources[], uint32_t resourceCount, ResourceStates before, ResourceStates after, uint32_t subResourceCount = -1) const override;

			// �����Ŏg�p����S�Ẵ��\�[�X�������Ă���f�[�^�ݒ�
			virtual void SetDescriptorHeaps(IDescriptorHeap* descriptorHeaps[], uint32_t heapCount = 1) const override;
			// �f�X�N���v�^�[�e�[�u���ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeDescriptorTable(IResourceView* view, uint32_t parameterIndex) const override;
			virtual void SetComputeDescriptorTable(IDescriptorHeap* heap, uint32_t parameterIndex) const override;

			// �V�F�[�_�[���\�[�X�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeShaderResource(IResource* resource, uint32_t parameterIndex) const override;
			// �萔�o�b�t�@�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeConstantBuffer(IResource* resource, uint32_t parameterIndex) const override;
			// �A���I�[�_�[�h�A�N�Z�X�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeUnorderedAccess(IResource* resource, uint32_t parameterIndex) const override;

			// 
			virtual void UnorderedAccessBarrier(IResource* resources[], uint32_t resourceCount) const override;
			// ���[�g�V�O�l�`���ݒ�(�R���s���[�g)
			virtual void SetComputeRootSignature(IRootSignature* rootSignature) const override;
			// ���[�g�V�O�l�`���ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsRootSignature(IRootSignature* rootSignature) const override;
			// �f�X�N���v�^�[�e�[�u���ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsRootDescriptorTable(IResourceView* view, uint32_t index) const override;
			// �V�F�[�_�[���\�[�X�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsShaderResource(IResource* resource, uint32_t index) const override;
			// �萔�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsConstantBuffer(IResource* resource, uint32_t index) const override;
			// �A���I�[�_�[�h�A�N�Z�X�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsUnorderedAccess(IResource* resource, uint32_t index) const override;
			// ���C�g���[�V���O�p�C�v���C���ݒ�
			virtual void SetRaytracingPipeline(IRaytracingPipeline* pipeline) const override;
			// ���X�^���C�U�[�p�C�v���C���ݒ�
			virtual void SetRasterizerPipeline(IRasterizerPipeline* pipeline) const override;

			// �R���s���[�g�p�C�v���C���ݒ�
			virtual void SetComputePipeline(IComputePipeline* pipeline) const override;

			// �v���~�e�B�u�ݒ�
			virtual void SetPrimitiveTopology(PrimitiveTopology topology) const override;
			// ���_�o�b�t�@�z��ݒ�
			virtual void SetVertexBuffers(IResource* resources[], uint64_t strides[], uint64_t sizes[], uint32_t start, uint32_t count) const override;
			// �C���f�b�N�X�o�b�t�@�ݒ�
			virtual void SetIndexBuffer(IResource* resource, uint64_t size, IndexFormat format) const override;
			// �V�[�U�[���N�g�z��ݒ�
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const override;
			// �r���[�|�[�g�z��ݒ�
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const override;
			// �����_�[�^�[�Q�b�g�z��ݒ�
			virtual void SetRenderTargets(IResourceView* renderTarget[], uint32_t count, IResourceView* depthStencil) const override;

			virtual void CopyResource(IResource* source, IResource* destination) const override;

			virtual void CopyBuffer(IResource* source, IResource* destination, uint64_t byteSize, uint32_t sourceOffset = 0, uint32_t destinationOffset = 0) const override;

			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const override;

			virtual void Close() const override;

			virtual void Reset() const override;

		};
	}

}