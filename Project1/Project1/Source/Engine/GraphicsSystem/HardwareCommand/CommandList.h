#pragma once
#include "..//..//Math/Color4.h"
#include <cstdint>
#include "../../Utility/AccessObject.h"
#include <iostream>

/*
�h����̃N���X�Ŋ֐��𐧌�����
*/

namespace Engine
{
	struct Rect;
	struct Viewport;

	namespace GraphicsSystem
	{
		class ICommandList;
		class ResourceView;
		class VertexBuffer;
		class IndexBuffer;
		class ConstantBuffer;
		class Texture;
		class RenderTexture;
		class DepthTexture;
		class Resource;
		class ResourceDescriptor;
		class RasterizerPipeline;
		class RaytracingPipeline;
		class ComputePipeline;
		class RootSignature;
		class ShaderTable;
		class BottomLevelAccelerationStructure;
		class TopLevelAccelerationStructure;
		class Buffer;

		enum class PrimitiveTopology : uint8_t;
		enum class ResourceStates : uint16_t;

		// �n�[�h�E�F�A�ōs�����������߂郊�X�g
		class CommandList : public AccessObject<CommandList>
		{
		private:
			using base = AccessObject<CommandList>;
		protected:
			using RenderTexturePtr = std::shared_ptr<RenderTexture>;
			using DepthTexturePtr = std::shared_ptr<DepthTexture>;
			using BottomLevelAccelerationStructurePtr = std::shared_ptr<BottomLevelAccelerationStructure>;
			using TopLevelAccelerationStructurePtr = std::shared_ptr<TopLevelAccelerationStructure>;
		protected:
			ICommandList* m_interface;
		public:
			// �R���X�g���N�^
			CommandList();
			// �f�X�g���N�^
			virtual ~CommandList();

			ICommandList* GetInterface() const;
		protected:
			// ���͈̔͂̓O���t�B�N�X�R�}���h���X�g�ȊO�̓A�N�Z�X�ł��Ȃ��悤�ɂ��܂�

			// �����_�[�^�[�Q�b�g���e�N���A
			virtual void ClearRenderTarget(ResourceView* view, const Rect& rect, const Color4& color = Color4::White) const;
			
			// �f�v�X�X�e���V�����e�N���A
			virtual void ClearDepthStencil(ResourceView* view, const Rect& rect, float depth = 1.0f, uint8_t stencil = 0) const;
			
			// ���_�o�b�t�@�z��ݒ�
			virtual void SetVertexBuffers(VertexBuffer* vertexBuffers[], uint32_t count, uint32_t start = 0) const;
			
			// �C���f�b�N�X�o�b�t�@�ݒ�
			virtual void SetIndexBuffer(IndexBuffer* indexBuffer) const;
			
			// �v���~�e�B�u�ݒ�
			virtual void SetTopology(PrimitiveTopology topology) const;
			
			// �r���[�|�[�g�z��ݒ�
			virtual void SetViewports(const Viewport viewports[], uint32_t count) const;
			
			// �V�U�[���N�g�z��ݒ�
			virtual void SetScissorRects(const Rect rects[], uint32_t count) const;
			
			// �����_�[�^�[�Q�b�g�z��,�f�v�X�X�e���V���ݒ�
			virtual void SetRenderTargets(RenderTexturePtr renderTargets[], uint32_t count, DepthTexturePtr depthStencil) const;
			
			// �f�X�N���v�^�[�q�[�v�z��ݒ�
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const;
			
			// ���X�^���C�U�[�p�C�v���C���ݒ�
			virtual void SetRasterizerPipeline(RasterizerPipeline* pipeline) const;
			
			// �萔�o�b�t�@�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const;
			
			// �V�F�[�_�[���\�[�X�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsShaderResource(Texture* texture, uint32_t registerIndex) const;
			
			// �A���I�[�_�[�h�A�N�Z�X�@�r���[������ݒ�(�O���t�B�b�N�X)
			virtual void SetGraphicsUnorderedAccess(Texture* texture, uint32_t registerIndex) const;
			
			// ���[�g�V�O�l�`���ݒ�@(�O���t�B�b�N�X)
			virtual void SetGraphicsRootSignature(RootSignature* rootSignature) const;
			
			// �f�X�N���v�^�[�e�[�u���ݒ� �K�v�ȏ�񂪘A���ō쐬����Ă���K�v����(�O���t�B�b�N�X)
			virtual void SetGraphicsDescriptorTable(ResourceView* headView, uint32_t registerIndex) const;
			
			// ���\�[�X�o���A�[
			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const;
			
			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const;

			// �`��
			virtual void DrawIndexedInstance(uint32_t useIndexCount, uint32_t instanceCount, uint32_t startIndex, uint32_t startVertex, uint32_t startInstance) const;
		protected:
			// ���C�g���[�V���O���s
			virtual void DispatchRaytracing(uint32_t width, uint32_t height, uint32_t depth, ShaderTable* rayGenerate, ShaderTable* hitGroup, ShaderTable* miss, ShaderTable* callable) const;

			// ���C�g���[�V���O�W�I���g���쐬
			virtual void BuildBottomLevelAS(BottomLevelAccelerationStructurePtr bottomLevelAS) const;

			// ���C�g���[�V���O�V�[������
			virtual void BuildTopLevelAS(TopLevelAccelerationStructurePtr topLevelAS) const;

			// �R���s���[�g�p�C�v���C���ݒ�
			virtual void SetComputePipeline(ComputePipeline* pipeline) const;

			// ���C�g���[�V���O�p�C�v���C���ݒ�
			virtual void SetRaytracingPipeline(RaytracingPipeline* pipeline) const;
			
			// �萔�o�b�t�@�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeConstantBuffer(ConstantBuffer* constantBuffer, uint32_t registerIndex) const;
			
			// �V�F�[�_�[���\�[�X�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeShaderResource(Texture* texture, uint32_t registerIndex) const;
			
			// �A���I�[�_�[�h�A�N�Z�X�@�r���[������ݒ�(�R���s���[�g)
			virtual void SetComputeUnorderedAccess(Texture* texture, uint32_t registerIndex) const;
			
			// ���[�g�V�O�l�`���ݒ�@(�R���s���[�g)
			virtual void SetComputeRootSignature(RootSignature* rootSignature) const;
			
			// �f�X�N���v�^�[�e�[�u���ݒ� �K�v�ȏ�񂪘A���ō쐬����Ă���K�v����(�R���s���[�g)
			virtual void SetComputeDescriptorTable(ResourceView* headView, uint32_t registerIndex) const;

			// �f�X�N���v�^�[�e�[�u���ݒ�
			virtual void SetComputeDescriptorTable(ResourceDescriptor* descriptor, uint32_t registerIndex) const;

			// �R���s���[�g�V�F�[�_�[���s
			virtual void DispatchCompute(uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) const;

			// �A���I�[�_�[�h�A�N�Z�X
			virtual void UnorderedAccessBarrier(Resource* resources[], uint32_t count) const;
			virtual void UnorderedAccessBarrier(Buffer* buffers[], uint32_t count) const;

		protected:
			
			// ���\�[�X�R�s�[
			virtual void CopyResource(Resource* source, Resource* destination) const;

			virtual void CopyBuffer(Buffer* buffer, uint32_t size, uint32_t srcOffset = 0, uint32_t dstOffset = 0) const;
			virtual void CopyBuffer(Buffer* buffer) const;

		public:
			// �R�}���h���s�I��
			void Close() const;
			// ���X�g���Z�b�g
			void Reset() const;
		};

	}
}