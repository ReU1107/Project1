#pragma once
#include <string>
#include <vector>
#include "..///Description/RaytracingPipelineDesc.h"

namespace Engine
{

	namespace GraphicsSystem 
	{

		class IRaytracingPipeline;
		class IShader;
		class ShaderLibrary;
		class RootSignature;
		struct RaytracingPipelineParameterDesc;

		class RaytracingPipeline
		{
			using Parameters = std::vector<RaytracingPipelineParameterDesc>;
		private:
			Parameters m_parameters;
			IRaytracingPipeline* m_interface;
		public:
			// �R���X�g���N�^
			RaytracingPipeline();
			// �f�X�g���N�^
			~RaytracingPipeline();

		public:
			// �p�����[�^�[�f�X�N�ǉ�
			void AddParameterDesc(const RaytracingPipelineParameterDesc& desc);

			// ���C�g���[�X�ő�񐔐ݒ�
			void SetRaytraceMaxCount(uint32_t maxCount);

			// �V�F�[�_�[���ݒ�
			void SetShaderConfig(uint32_t attributeSize, uint32_t payloadSize);

			// �g�ݍ��킹�ݒ�
			void AddAssociation(const wchar_t** shaderNames, uint32_t shaderCount, int32_t index = -1);

			// �V�F�[�_�[���C�u�����ǉ�
			void AddShaderLibrary(ShaderLibrary* shaderLibrary);

			// ���[�J�����[�g�V�O�l�`���ݒ�
			void AddLocalRootSignature(RootSignature* localRootSignature, const wchar_t** usedShaders, uint32_t shaderCount);
			// �O���[�o�����[�g�V�O�l�`���ݒ�
			void AddGlobalRootSignature(RootSignature* globalRootSignature);
			
			// �q�b�g�O���[�v�ǉ�
			void AddHitGroup(const wchar_t* groupName, const wchar_t* hitShaderName, const wchar_t* intersectShaderName = nullptr, const wchar_t* anyHitShaderName = nullptr);

			// �p�C�v���C���쐬
			void Create();

			// �V�F�[�_�[���ʎq�擾
			void* GetShaderIdentifier(const wchar_t* exportName) const;

			IRaytracingPipeline* GetInterface() const;

			void SetName(const std::wstring& name);
		};

	}

}