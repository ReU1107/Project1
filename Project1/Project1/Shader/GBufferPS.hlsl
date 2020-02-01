#include "MeshHeader.hlsli"
#include "Material.hlsli"

ConstantBuffer<Material> materialBuffer: register(b0);
Texture2D tex : register(t0);
SamplerState sam : register(s0);

struct PSOutput
{
	float4 albedo : SV_TARGET0;
	float4 normal : SV_TARGET1;
	float4 diffuse : SV_TARGET2;
	float4 specular : SV_TARGET3;
};

PSOutput main(in PSInput input)
{
	PSOutput output = (PSOutput)0;
	output.albedo = tex.Sample(sam, input.texcoord);
	if (output.albedo.a < 0.1f)
		discard;

	output.normal = float4(input.normal,1.0f);
	output.diffuse = float4(materialBuffer.diffuseCoeff, 1.0f);
	output.specular.rgb = materialBuffer.specularCoeff;
	output.specular.a = materialBuffer.specularity;

	return output;
}