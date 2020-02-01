#pragma once
#include <cstdint>

/*
D3D12_RAYTRACING_SHADER_CONFIG
*/

/*
payload		���C�g���[�X���I�������ۂɕԂ������
float3 color��
attribute	�Փ˔��肪�N�������ۂɕԂ������
float2 xy;	���������O�p�`�̂��ꂼ��̊����l��
*/
namespace Engine 
{

	namespace GraphicsSystem 
	{
		// ���C�g���[�V���O�V�F�[�_�[���
		struct RaytracingShaderConfigDesc
		{
			uint32_t attributeSize;		// �������i�[�T�C�Y
			uint32_t payloadSize;		// 
		};
	}
}

