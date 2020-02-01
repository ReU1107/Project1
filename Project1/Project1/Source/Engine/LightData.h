#pragma once

#include "Utility/ShaderCommonData.h"
#include "Math/Color3.h"

struct LightData
{
	Engine::Color3 color;		// �F
	float3 position;	// �ʒu
	float3 direction;	// ����
	float range;		// �͈�
	float angle;		// �A���O��

	uint type;			// ���
};