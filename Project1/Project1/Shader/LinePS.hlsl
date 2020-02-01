struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(in PSInput input) : SV_TARGET
{
	return input.color;
}