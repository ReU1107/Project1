#include "Shading.hlsli"

struct PSInput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

Texture2D albedoTex : register(t0);
Texture2D normalTex : register(t1);
Texture2D diffuseTex : register(t2);
Texture2D specularTex : register(t3);
Texture2D depthTex : register(t4);
Texture2D shadowTex : register(t5);

SamplerState sam : register(s0);

//StructuredBuffer<Light> lightList : register(t5);
struct C
{
	uint lightCount;
};
//ConstantBuffer<C> c : register(b0);

float4 main(in PSInput input) : SV_TARGET
{
	float4 color = float4(0.0f, 1.0f, 1.0f, 1.0f);	
	float4 albedoColor = albedoTex.Sample(sam, input.texcoord);
	//float3 normal = normalTex.Sample(sam, input.texcoord).rgb;
	//float3 depth = depthTex.Sample(sam, input.texcoord).rgb;
	//float3 diffuse = diffuseTex.Sample(sam, input.texcoord).rgb;
	//float4 specular = specularTex.Sample(sam, input.texcoord);

	float4 shadow = shadowTex.Sample(sam, input.texcoord);

	//for (uint i = 0; i < c.lightCount; ++i)
	//{
	//	Light light = lightList.Load(i);
	//	

	//}

	color = albedoColor;
	color *= shadow;

	return color;
}