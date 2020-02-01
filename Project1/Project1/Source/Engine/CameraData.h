#pragma once
#include "Utility/ShaderCommonData.h"

struct CameraData
{
	float4x4 viewMatrix;			// �r���[�ϊ��s��
	float4x4 projectionMatrix;		// �v���W�F�N�V�����ϊ��s��
	float4x4 viewProjectionMatrix;	// �r���[�v���W�F�N�V�����ϊ��s��
	float4x4 projViewMatrix;
	float4 position;
};