#pragma once
#include "CommandList.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine
{
	namespace GraphicsSystem
	{
		// GPGPU�݂̂ŏ���������̂������߂邱�Ƃ̂ł��郊�X�g
		class ComputeCommandList : public CommandList
		{
		private:
			using base = CommandList;
			using ComputeCommandListPtr = std::shared_ptr<ComputeCommandList>;
		public:
			// �R���X�g���N�^
			ComputeCommandList();
			// �f�X�g���N�^
			virtual ~ComputeCommandList();

			static ComputeCommandListPtr Create(const std::string& name);
		public:
			// �f�X�N���v�^�[�ݒ�
			virtual void SetDescriptorHeaps(ResourceDescriptor* descriptors[], uint32_t count) const override;

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

			virtual void ResourceBarrier(Resource* resources[], uint32_t count, ResourceStates after) const override;

			virtual void ResourceBarrier(Buffer* buffers[], uint32_t count, ResourceStates after) const override;

			// ���\�[�X�R�s�[
			virtual void CopyResource(Resource* source, Resource* destination) const override;

			virtual void CopyBuffer(Buffer* buffer) const override;
		};
	}
}