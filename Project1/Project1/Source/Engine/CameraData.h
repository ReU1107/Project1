#pragma once
#include "Utility/ShaderCommonData.h"

struct CameraData
{
	float4x4 viewMatrix;			// ビュー変換行列
	float4x4 projectionMatrix;		// プロジェクション変換行列
	float4x4 viewProjectionMatrix;	// ビュープロジェクション変換行列
	float4x4 projViewMatrix;
	float4 position;
};