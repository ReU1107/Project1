#include "SpriteHeader.hlsli"

VSOutput main(in VSInput input)
{
	const float2 Resolution = float2(1280.0f, 960.0f);

	const float2 texcoord[4] = {
		{ 0.0f,0.0f }, { 1.0f,0.0f },
		{ 0.0f,1.0f }, { 1.0f,1.0f }
	};

	float2 poisition = ((input.position * float2(2.0f, -2.0f)) / Resolution) + float2(-1.0f, 1.0f);
	VSOutput output = (VSOutput)0;
	output.position = float4(poisition, 0.1f, 1.0f);
	output.texcoord = texcoord[input.index];

	return output;
}
