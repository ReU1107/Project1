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
				RaytracingPipelineConfigDesc pipelineConfig;	// パイプラインコンフィグ
				RaytracingShaderConfigDesc shaderConfig;;		// シェーダーコンフィグ
				RaytracingAssociationDesc association;			// 2つを関連づける
				RaytracingShaderLibraryDesc shaderLibrary;		// ライブラリー
				RaytracingSignatureDesc signature;				// シグネチャ
				RaytracingHitGroupDesc hitGroup;				// ヒットグループ

			};

			RaytracingPipelineParameterType parameterType;		// パラメータのタイプ

			RaytracingPipelineParameterDesc()
				: pipelineConfig()
				, parameterType()
			{
			}
		};
	}
}