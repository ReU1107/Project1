#pragma once
#include <cstdint>

namespace Engine
{
	struct Rect;
	struct Viewport;

	namespace GraphicsSystem 
	{

		class IResource;
		class IResourceView;
		class IDescriptorHeap;
		class IRootSignature;
		class IRasterizerPipeline;
		class IRaytracingPipeline;
		class IComputePipeline;
		class IAccelerationStructure;

		struct RaytracingDispatchDesc;
		struct RasterizerPipelineDesc;
		enum class ResourceStates : uint16_t;
		enum class PrimitiveTopology : uint8_t;
		enum class IndexFormat : uint8_t;

		class ICommandList
		{
		public:
			// ���z�f�X�g���N�^
			virtual ~ICommandList() {}

			virtual void* GetNativeCommandList() const = 0;

			virtual void ClearRenderTarget(IResourceView* renderTargetView, const Rect& rect, float color[4]) const = 0;

			virtual void ClearDepthStencil(IResourceView* depthStencilView, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const = 0;

			virtual void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) const = 0;

			// 
			virtual void BuildBottomLevelAccelerationStructure(IAccelerationStructure* as) const = 0;

			// �V�[���쐬�R�}���h���s
			virtual void BuildTopLevelAccelerationStructure(IAccelerationStructure* as) const = 0;

			// ���C�g���[�V���O���s�R�}���h���s
			virtual void DispatchRaytracing(const RaytracingDispatchDesc& desc) const = 0;
			// ���\�[�X�̎d�l���@��ύX���Ӑ}���Ȃ��A�N�Z�X��h���܂�
			virtual void ResourceBarrierTransition(IResource* resources[], uint32_t resourceCount, ResourceStates before, ResourceStates after, uint32_t subResourceCount = -1) const = 0;

			// �����Ŏg�p����S�Ẵ��\�[�X�������Ă���f�[�^�ݒ�
			virtual void SetDescriptorHeaps(IDescriptorHeap* descriptorHeaps[], uint32_t heapCount = 1) const = 0;
			// �f�X�N���v�^�[�e�[�u���ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeDescriptorTable(IResourceView* view, uint32_t parameterIndex) const = 0;
			virtual void SetComputeDescriptorTable(IDescriptorHeap* heap, uint32_t parameterIndex) const = 0;

			// �V�F�[�_�[���\�[�X�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeShaderResource(IResource* resource, uint32_t parameterIndex) const = 0;
			// �萔�o�b�t�@�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeConstantBuffer(IResource* resource, uint32_t parameterIndex) const = 0;
			// �A���I�[�_�[�h�A�N�Z�X�r���[�ݒ�(�R���s���[�g�V�F�[�_�[)
			virtual void SetComputeUnorderedAccess(IResource* resource, uint32_t parameterIndex) const = 0;

			// 
			virtual void UnorderedAccessBarrier(IResource* resources[], uint32_t resourceCount) const = 0;
			// ���[�g�V�O�l�`���ݒ�(�R���s���[�g)
			virtual void SetComputeRootSignature(IRootSignature* rootSignature) const = 0;
			// ���[�g�V�O�l�`���ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsRootSignature(IRootSignature* rootSignature) const = 0;
			// �f�X�N���v�^�[�e�[�u���ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsRootDescriptorTable(IResourceView* view, uint32_t index) const = 0;
			// �V�F�[�_�[���\�[�X�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsShaderResource(IResource* resource, uint32_t index) const = 0;
			// �萔�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsConstantBuffer(IResource* resource, uint32_t index) const = 0;
			// �A���I�[�_�[�h�A�N�Z�X�r���[�ݒ�(�O���t�B�b�N)
			virtual void SetGraphicsUnorderedAccess(IResource* resource, uint32_t index) const = 0;
			// ���C�g���[�V���O�p�C�v���C���ݒ�
			virtual void SetRaytracingPipeline(IRaytracingPipeline* pipeline) const = 0;
			// ���X�^���C�U�[�p�C�v���C���ݒ�
			virtual void SetRasterizerPipeline(IRasterizerPipeline* pipeline) const = 0;

			virtual void SetComputePipeline(IComputePipeline* pipeline) const = 0;

			// �v���~�e�B�u�ݒ�
			virtual void SetPrimitiveTopology(PrimitiveTopology topology) const = 0;
			// ���_�o�b�t�@�z��ݒ�
			virtual void SetVertexBuffers(IResource* resource[], uint64_t strides[], uint64_t sizes[], uint32_t start, uint32_t count) const = 0;
			// �C���f�b�N�X�o�b�t�@�ݒ�
			virtual void SetIndexBuffer(IResource* resource, uint64_t size, IndexFormat format) const = 0;
			// �V�[�U�[���N�g�z��ݒ�
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const = 0;
			// �r���[�|�[�g�z��ݒ�
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const = 0;
			// �����_�[�^�[�Q�b�g�z��ݒ�
			virtual void SetRenderTargets(IResourceView* renderTarget[], uint32_t count, IResourceView* depthStencil) const = 0;

			// ���\�[�X�R�s�[
			virtual void CopyResource(IResource* source, IResource* destination) const = 0;

			virtual void CopyBuffer(IResource* source, IResource* destination, uint64_t byteSize, uint32_t sourceOffset, uint32_t destinationOffset) const = 0;

			// 
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const = 0;

			// 
			virtual void Close() const = 0;

			// 
			virtual void Reset() const = 0;

		};

	}
}