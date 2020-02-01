#include "RaytracingStruct.hlsli"

// グローバル情報

// シーン情報(toplevel,bottomlevel)
RaytracingAccelerationStructure	scene : register(t0);
// 書き込み先のテクスチャ
RWTexture2D<float4> outputTexture : register(u0);

ConstantBuffer<SceneData> sceneBuffer : register(b0);
ConstantBuffer<CameraData> cameraBuffer : register(b1);
StructuredBuffer<LightData> lightBuffer : register(t1);

// ローカル情報
StructuredBuffer<float3> normalBuffer : register(t0, space1);
//StructuredBuffer<float2> uvBuffer : register(t1, space1);
ByteAddressBuffer indexBuffer : register(t2, space1);
//Texture2D tex : register(t3, space1);
//SamplerState sam : register(s0);

uint3 Get32bitIndices(uint primIdx)
{
	uint indexOffset = primIdx * 4 * 3;
	uint3 ret = indexBuffer.Load3(indexOffset);
	return ret;
}

[shader("raygeneration")]
void RayGenerateShader()
{
	// ピクセル中心座標をクリップ空間座標に変換
	uint2 index = DispatchRaysIndex().xy;
	float2 xy = (float2)index;
	// -1～1にする
	float2 clipSpacePos = xy / float2(DispatchRaysDimensions().xy) * float2(2, -2) + float2(-1, 1);

	// クリップ空間座標をワールド空間座標に変換
	float4 worldPos = mul(cameraBuffer.projViewMatrix, float4(clipSpacePos, 1, 1));

	// ワールド空間座標とカメラ位置からレイを生成
	worldPos.xyz /= worldPos.w;
	float3 origin = cameraBuffer.position.xyz;
	float3 direction = normalize(worldPos.xyz - origin);

	RayDesc ray;
	ray.Origin = origin;
	ray.Direction = direction;

	ray.TMin = 0;
	ray.TMax = 10000;

	Payload payload;
	payload.color = float4(0, 0, 0, 1);
	payload.traceCount = 1;
	TraceRay(scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, 0xff, 0, 2, 0, ray, payload);

	outputTexture[index.xy] = payload.color;
}

[shader("miss")]
void MissShader(inout Payload payload)
{
	payload.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
}

// 影の影響を受けるか判断するシェーダー
[shader("closesthit")]
void ShadowCheckShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
{
	uint3 indices = Get32bitIndices(PrimitiveIndex());

	float3 normal = normalBuffer[indices.x] +
		attribute.barycentrics.x * (normalBuffer[indices.y] - normalBuffer[indices.x]) +
		attribute.barycentrics.y * (normalBuffer[indices.z] - normalBuffer[indices.x]);

	normal = normalize(normal);

	float4 color = float4(1, 1, 1, 1);

	float t = RayTCurrent();
	float3 rayDirection = WorldRayDirection();
	float3 rayOrigin = WorldRayOrigin();

	float3 position = rayOrigin + t * rayDirection;
	float3 offset = normal * 0.05f;
	float shadow = 1.0f;

	for (uint i = 0; i < sceneBuffer.lightCount; ++i)
	{
		LightData light = lightBuffer.Load(i);
		float distance = length(abs(light.position - position));
		// 距離の方が長いなら範囲外とみなし
		//if (light.range < distance)
		//{
		//	shadow = 0.25f;
		//	break;
		//}
		float3 lightDirection = normalize(light.position - (position + offset));

		RayDesc ray;
		ray.Origin = position + offset;
		ray.Direction = lightDirection;

		ray.TMin = 0.01f;
		ray.TMax = length(light.position - position);

		ShadowPayload shadowPayload;
		shadowPayload.shadowCoeff = 1.0f;

		TraceRay(scene, 0, ~0b00000001, 1, 2, 1, ray, shadowPayload);
		shadow *= shadowPayload.shadowCoeff;
	}
	
	color.rgb *= shadow;

	//color.rgb = normal;

	payload.color = color;
}

[shader("closesthit")]
void NoneShadowCheckShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
{
	float4 color = float4(1, 1, 1, 1);
	payload.color = color;
}

[shader("anyhit")]
void AlphaCheckShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
{
	//uint3 indices = Get32bitIndices(PrimitiveIndex());

	//float2 uvs[3] = {
	//	uvBuffer[indices.x],
	//	uvBuffer[indices.y],
	//	uvBuffer[indices.z]
	//};

	//float2 uv = uvs[0] +
	//	attribute.barycentrics.x * (uvs[1] - uvs[0]) +
	//	attribute.barycentrics.y * (uvs[2] - uvs[0]);

	//float alpha = tex.SampleLevel(sam, uv, 0.0).a;
	//if (alpha < 0.01f)
	//{
	//	IgnoreHit();
	//}

}

[shader("closesthit")]
void ShadowHitShader(inout ShadowPayload payload, BuiltInTriangleIntersectionAttributes attribute)
{
	// 距離が遠いほど影を薄くする必要がある
	float t = RayTCurrent();
	float s = 0.5f;
	float r = clamp(t * 4.0f / 10000.0f, 0.1f, 0.9f);
	payload.shadowCoeff = 1.0f - s + r * s;
}

[shader("miss")]
void ShadowMissShader(inout ShadowPayload payload)
{
	// 影ができる　≒　RGBの値が減る
	// 当たらなかったため
	payload.shadowCoeff = 1.0f;
}