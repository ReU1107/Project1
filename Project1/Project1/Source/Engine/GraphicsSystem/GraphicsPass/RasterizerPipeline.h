#pragma once
#include <vector>
#include <array>
#include <cstdint>
#include "..//Description/BlendDesc.h"
#include "..//Description/InputLayoutDesc.h"
#include "..//Description/RasterizerDesc.h"
#include "..//Description/DepthStencilDesc.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class Shader;
		class Texture;
		class RootSignature;
		class IRasterizerPipeline;
		enum class ResourceFormat : uint8_t;
		enum class PrimitiveTopology : uint8_t;

		class RasterizerPipeline
		{
		private:
			using Textures = std::vector<Texture*>;

		private:
			IRasterizerPipeline* m_interface;		// �C���^�[�t�F�C�X
			Textures m_renderTargets;				// �����_�[�^�[�Q�b�g�z��
			Shader* m_vertexShader;					// ���_�V�F�[�_�[
			Shader* m_pixelShader;					// �s�N�Z���V�F�[�_�[
			Shader* m_domainShader;					// �h���C���V�F�[�_�[
			Shader* m_hullShader;					// �n���V�F�[�_�[
			Shader* m_geometryShader;				// �W�I���g���V�F�[�_�[
			RootSignature* m_rootSignature;			// ���[�g�V�O�l�`��
			RasterizerDesc m_rasterizerState;		// ���X�^���C�U�[�X�e�[�g
			BlendDesc m_blendState;					// �u�����h�X�e�[�g
			InputLayoutDesc m_inputLayout;			// �C���v�b�g���C�A�E�g
			DepthStencilDesc m_depthStencilState;	// �f�v�X�X�e���V���X�e�[�g
			uint32_t m_sampleCount;					// �T���v���J�E���g
			uint32_t m_sampleQuality;				// �T���v���N�I���e�B
			uint32_t m_renderTargetCount;			// �����_�[�^�[�Q�b�g��
			uint32_t m_nodeMask;					// �m�[�h�}�X�N
			uint32_t m_sampleMask;					// �T���v���}�X�N
			PrimitiveTopology m_topology;			// �`��
			ResourceFormat m_renderTargetFormats[8];// �����_�����O�^�[�Q�b�g�t�H�[�}�b�g
			ResourceFormat m_depthStencilFormat;	// �f�v�X�X�e���V���t�H�[�}�b�g
		public:
			// �R���X�g���N�^
			RasterizerPipeline();
			// �f�X�g���N�^
			~RasterizerPipeline();
			// ���_�V�F�[�_�[�ݒ�
			void SetVertexShader(Shader* shader);
			// �s�N�Z���V�F�[�_�[�ݒ�
			void SetPixelShader(Shader* shader);
			// ���[�g�V�O�l�`���ݒ�
			void SetRootSignature(RootSignature* rootSignature);
			// ���̓��C�A�E�g�ݒ�
			void SetInputLayout(const InputLayoutDesc& inputLayout);
			// �u�����h�X�e�[�g�ݒ�
			void SetBlendState(const BlendDesc& blendDesc);
			// ���X�^���C�Y�X�e�[�g�ݒ�
			void SetRasterizerState(const RasterizerDesc& rasterizerDesc);
			// �f�v�X�X�e���V���X�e�[�g�ݒ�
			void SetDepthStencilState(const DepthStencilDesc& depthStencilDesc);
			// �T���v���f�X�N�ݒ�
			void SetSampleDesc(uint32_t sampleCount = 1, uint32_t sampleQuality = 0);
			// �����_�[�^�[�Q�b�g���ݒ�
			void SetRenderTargetCount(uint32_t renderTargetCount);
			// �����_�[�^�[�Q�b�g�t�H�[�}�b�g�ݒ�
			void SetRenderTargetFormat(ResourceFormat format, int32_t index);
			// �f�v�X�X�e���V���t�H�[�}�b�g�ݒ�
			void SetDepthStencilFormat(ResourceFormat format);

			void Create();
			// �C���^�[�t�F�C�X�擾
			IRasterizerPipeline* GetInterface() const;
			// ���[�g�V�O�l�`���擾
			RootSignature* GetRootSignature() const;

			// ���_�V�F�[�_�[�擾
			Shader* GetVertexShader() const;
			// �s�N�Z���V�F�[�_�[�擾
			Shader* GetPixelShader() const;

		};

	}
}