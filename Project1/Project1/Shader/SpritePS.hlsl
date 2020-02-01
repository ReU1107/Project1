#include "SpriteHeader.hlsli"

Texture2D tex : register(t0);
SamplerState sam : register(s0);

float4 main(in PSInput input) : SV_TARGET
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	color = tex.Sample(sam, input.texcoord);

	return color;
}