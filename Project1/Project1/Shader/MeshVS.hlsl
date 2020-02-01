#include "MeshHeader.hlsli"

struct CameraData
{
	float4x4 viewMatrix;			// ビュー変換行列
	float4x4 projectionMatrix;		// プロジェクション変換行列
	float4x4 viewProjectionMatrix;	// ビュープロジェクション変換行列
};

struct ModelData
{
	float4x4 worldMatrix;
};

ConstantBuffer<CameraData> cameraBuffer : register(b0);

ConstantBuffer<ModelData> modelBuffer : register(b1);

VSOutput main(in VSInput input)
{
	float4x4 worldMatrix = modelBuffer.worldMatrix;
	VSOutput output = (VSOutput)0;

	float4x4 mat = mul(cameraBuffer.viewProjectionMatrix, worldMatrix);
	float4 position = mul(mat, float4(input.position, 1.0f));
	//float4 position = mul(float4(input.position, 1.0f), mat);
	float3 normal = mul((float3x3)worldMatrix, input.normal);

	output.position = position;
	output.normal = normal;
	output.texcoord = input.texcoord;
	
	return output;
}