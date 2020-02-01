#pragma once
#include <cstdint>
#include "RaytracingAssociationDesc.h"
#include "RaytracingHitGroupDesc.h"
#include "RaytracingShaderLibraryDesc.h"
#include "RaytracingPipelineConfigDesc.h"
#include "RaytracingShaderConfigDesc.h"
#include "RaytracingSignatureDesc.h"

namespace Engine 
{

	namespace GraphicsSystem 
	{

		enum class RaytracingPipelineParameterType : uint8_t;

		struct RaytracingPipelineParameterDesc
		{
			union
			{
				RaytracingPipelineConfigDesc pipelineConfig;	// �p�C�v���C���R���t�B�O
				RaytracingShaderConfigDesc shaderConfig;;		// �V�F�[�_�[�R���t�B�O
				RaytracingAssociationDesc association;			// 2���֘A�Â���
				RaytracingShaderLibraryDesc shaderLibrary;		// ���C�u�����[
				RaytracingSignatureDesc signature;				// �V�O�l�`��
				RaytracingHitGroupDesc hitGroup;				// �q�b�g�O���[�v

			};

			RaytracingPipelineParameterType parameterType;		// �p�����[�^�̃^�C�v

			RaytracingPipelineParameterDesc()
				: pipelineConfig()
				, parameterType()
			{
			}
		};
	}
}