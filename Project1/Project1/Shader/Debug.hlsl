struct PSInput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

Texture2D tex : register(t0);
SamplerState sam : register(s0);

float4 main(in PSInput input) : SV_TARGET
{
	return tex.Sample(sam,input.texcoord);
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}