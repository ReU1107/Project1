#include "MeshHeader.hlsli"

Texture2D tex : register(t0);
SamplerState sam : register(s0);
/*
マルチレンダーターゲットを使用する際にはターゲットを増やしてください
増やす際はアプリケーションの方と同じ順番にしてください
*/
struct PSOutput
{
	float4 color : SV_TARGET0;
};

float4 main(in PSInput input) : SV_TARGET
{
	float4 color = tex.Sample(sam,input.texcoord);
	// アルファテスト
	if (color.a < 0.01f)
	{
		//discard;
	}
	//color.rgb = input.normal;
	color.a = 1.0f;
	return color;
	
	//return float4(0.0f, 1.0f, 1.0f, 1.0f);
}