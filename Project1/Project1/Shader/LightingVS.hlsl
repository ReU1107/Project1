struct VSInput
{
	float2 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

VSOutput main(in VSInput input)
{
	VSOutput output = (VSOutput)0;
	output.position = float4(input.position, 0.1f, 1.0f);
	output.texcoord = input.texcoord;
	return output;
}