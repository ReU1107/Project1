#include "PreZHeader.hlsli"

struct SceneData
{
	float4x4 ViewProjectionMatrix;	// ビュープロジェクション合成変換行列
};

struct MeshData
{
	float4x4 WorldMatrix;	// ワールド変換行列
};

ConstantBuffer<SceneData> sceneBuffer : register(b0);
ConstantBuffer<MeshData> meshBuffer : register(b1);


VSOutput main(in VSInput input)
{
	float4x4 worldMatrix = float4x4(
		float4(1.0f, 0.0f, 0.0f, 0.0f),
		float4(0.0f, 1.0f, 0.0f, 0.0f),
		float4(0.0f, 0.0f, 1.0f, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	VSOutput output = (VSOutput)0;
	float4x4 mat = mul(worldMatrix, sceneBuffer.ViewProjectionMatrix);
	float4 position = mul(mat, float4(input.position, 1.0f));

	return output;
}