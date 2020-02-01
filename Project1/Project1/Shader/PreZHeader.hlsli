struct VSInput
{
	float3 position : POSITION;
};

struct VSOutput
{
	float4 position : SV_POSITION;
};

typedef VSOutput PSInput;