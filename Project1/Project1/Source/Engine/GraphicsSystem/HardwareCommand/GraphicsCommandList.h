#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		class GraphicsCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using GraphicsCommandListPtr = std::shared_ptr<GraphicsCommandList>;
		public:
			// �R���X�g���N�^
			GraphicsCommandList();
			// �f�X�g���N�^
			virtual ~GraphicsCommandList();

			static GraphicsCommandListPtr Create(const std::string& name);

		public:
			// �����_�[�^�[�Q�b�g���e�N���A
			virtual void ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color = Color4::White) const override;

			// �f�v�X�X�e���V�����e�N���A
			virtual void ClearDepthStencil(ResourceView* view, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const override;

			// ���_�o�b�t�@�z��ݒ�
			virtual void SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start = 0) const override;

			// �C���f�b�N�X�o�b�t�@�ݒ�
			virtual void SetIndexBuffer(IndexBuffer* indexBuffer) const override;

			// �v���~�e�B�u�ݒ�
			virtual void SetTopology(PrimitiveTopology topology) const override;

			// �r���[�|�[�g�z��ݒ�
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const override;

			// �V�U�[���N�g�z��ݒ�
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const override;

			// �����_�[�^�[�Q�b�g�z��,�f�v�X�X�e���V���ݒ�
			virtual void SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const override;

			// �f�X�N���v�^�[�q�[�v�z��ݒ�
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const override;

			// ���X�^���C�U�[�p�C�v���C���ݒ�
			virtual void SetRasterizerPipeline(RasterizerPipeline* pipeline) const override;

			// �萔�o�b�t�@�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const override;

			// �V�F�[�_�[���\�[�X�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const override;

			// �A���I�[�_�[�h�A�N�Z�X�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const override;

			// ���[�g�V�O�l�`���ݒ�@(�O���t�B�b�N�X)
			virtual void SetGraphicsRootSignature(RootSignature* rootSignature) const override;

			// �f�X�N���v�^�[�e�[�u���ݒ� �K�v�ȏ�񂪘A���ō쐬����Ă���K�v����(�O���t�B�b�N�X)
			virtual void SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const override;

			// ���\�[�X�o���A�[
			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const override;

			// �`��
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t startVertex = 0, uint32_t startInstance = 0) const override;

			// ���C�g���[�V���O���s
			virtual void DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const override;

			// ���C�g���[�V���O�W�I���g���쐬
			virtual void BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const override;

			// ���C�g���[�V���O�V�[������
			virtual void BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const override;

			// ���C�g���[�V���O�p�C�v���C���ݒ�
			virtual void SetRaytracingPipeline(RaytracingPipeline* pipeline) const override;

			// �R���s���[�g�p�C�v���C���ݒ�
			virtual void SetComputePipeline(ComputePipeline* pipeline) const override;

			// �萔�o�b�t�@�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const override;

			// �V�F�[�_�[���\�[�X�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const override;

			// �A���I�[�_�[�h�A�N�Z�X�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const override;

			// ���[�g�V�O�l�`���ݒ�@(�R���s���[�g)
			virtual void SetComputeRootSignature(RootSignature* rootSignature) const override;

			// �f�X�N���v�^�[�e�[�u���ݒ� �K�v�ȏ�񂪘A���ō쐬����Ă���K�v����(�R���s���[�g)
			virtual void SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const override;
			virtual void SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const override;

			// �R���s���[�g�V�F�[�_�[���s
			virtual void DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const override;

			// 
			virtual void UnorderedAccessBarrier(Resource* resources[], uint32_t count) const override;

			virtual void UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const override;

			// ���\�[�X�R�s�[
			virtual void CopyResource(Resource* source, Resource* destination) const override;


			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const override;

			virtual void CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset = 0, uint32_t dstOffset = 0) const;
			virtual void CopyBuffer(Buffer* buffer) const override;
		};

	}
}