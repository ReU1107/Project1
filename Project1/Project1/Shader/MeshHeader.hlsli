
struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct SceneData
{
	float4x4 ViewProjectionMatrix;	// ビュープロジェクション合成変換行列
};

struct MeshData
{
	float4x4 WorldMatrix;	// ワールド変換行列
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAl;
	float2 texcoord : TEXCOORD;
};

typedef VSOutput PSInput;
