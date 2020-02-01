
struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct SceneData
{
	float4x4 ViewProjectionMatrix;	// �r���[�v���W�F�N�V���������ϊ��s��
};

struct MeshData
{
	float4x4 WorldMatrix;	// ���[���h�ϊ��s��
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAl;
	float2 texcoord : TEXCOORD;
};

typedef VSOutput PSInput;
