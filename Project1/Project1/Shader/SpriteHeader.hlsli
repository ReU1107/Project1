struct VSInput
{
	float2 position : POSITION;	// ���_���W
	uint index : SV_VERTEXID;	// �V�X�e���l�̒��_ID�������Ă���
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

typedef VSOutput PSInput;
