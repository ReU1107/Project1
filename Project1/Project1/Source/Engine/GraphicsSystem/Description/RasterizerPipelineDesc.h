#pragma once
#include <cstdint>
#include "InputLayoutDesc.h"
#include "RasterizerDesc.h"
#include "BlendDesc.h"
#include "DepthStencilDesc.h"
#include "..//Enumerations/PrimitiveTopology.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class IRootSignature;
		class IShader;
		enum class ResourceFormat : uint8_t;

		struct RasterizerPipelineDesc
		{
			IRootSignature* rootSignature;			// ���[�g�V�O�l�`��
			InputLayoutDesc inputLayout;			// �C���v�b�g���C�A�E�g
			RasterizerDesc rasterizerState;			// ���X�^���C�U�[�X�e�[�g
			BlendDesc blendState;					// �u�����h�X�e�[�g
			DepthStencilDesc depthStencil;			// �f�v�X�X�e���V���X�e�[�g
			IShader* vertexShader;					// ���_�V�F�[�_�[
			IShader* domainShader;					// �h���C���V�F�[�_�[
			IShader* hullShader;					// �n���V�F�[�_�[
			IShader* geometryShader;				// �W�I���g���[�V�F�[�_�[
			IShader* pixelShader;					// �s�N�Z���V�F�[�_�[
			uint32_t renderTargetCount;				// �����_�[�^�[�Q�b�g��
			uint32_t sampleMask;					// �T���v���}�X�N
			uint32_t nodeMask;						// �m�[�h�}�X�N
			uint32_t sampleCount;					// �T���v���J�E���g
			uint32_t sampleQuality;					// �T���v���N�I���e�B
			PrimitiveTopology topology;				// �g�b�|���W�[
			ResourceFormat renderTargetFormats[8];	// �����_�[�^�[�Q�b�g�t�H�[�}�b�g�z��
			ResourceFormat depthStencilFormat;		// �f�v�X�X�e���V���t�H�[�}�b�g
		};
		/*
		D3D12_STREAM_OUTPUT_DESC StreamOutput;
		D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;
		D3D12_CACHED_PIPELINE_STATE CachedPSO;
		 Flags;
		*/
		
	}

}