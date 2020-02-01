//#include "RaytracingStruct.hlsli"
//
//// �O���[�o�����
//
//// �V�[�����(toplevel,bottomlevel)
//RaytracingAccelerationStructure	scene : register(t0);
//// �������ݐ�̃e�N�X�`��
//RWTexture2D<float4> outputTexture : register(u0);
//
//ConstantBuffer<SceneData> sceneBuffer : register(b0);
//ConstantBuffer<CameraData> cameraBuffer : register(b1);
//StructuredBuffer<LightData> lightBuffer : register(t1);
//
//// �T���v���[�X�e�[�g
//SamplerState sam : register(s0);
//
//// ���[�J�����
//// ��������T�u���b�V��1��1�̃f�[�^
//ConstantBuffer<MaterialData> materialBuffer : register(b0, space1);
//StructuredBuffer<float3> normalBuffer : register(t0, space1);
//StructuredBuffer<float2> uvBuffer : register(t1, space1);
//ByteAddressBuffer indexBuffer : register(t2, space1);
//Texture2D tex : register(t3, space1);
//
////StructuredBuffer<ProceduralInstance> proceduralBuffer : register(t0, space1);
//
//uint3 Get32bitIndices(uint primIdx)
//{
//	uint indexOffset = primIdx * 4 * 3;
//	uint3 ret = indexBuffer.Load3(indexOffset);
//	return ret;
//}
//
//[shader("raygeneration")]
//void RayGenerateShader()
//{
//	// �s�N�Z�����S���W���N���b�v��ԍ��W�ɕϊ�
//	uint2 index = DispatchRaysIndex().xy;
//	float2 xy = (float2)index;
//	// -1�`1�ɂ���
//	float2 clipSpacePos = xy / float2(DispatchRaysDimensions().xy) * float2(2, -2) + float2(-1, 1);
//
//	// �N���b�v��ԍ��W�����[���h��ԍ��W�ɕϊ�
//	float4 worldPos = mul(sceneBuffer.projToWorld, float4(clipSpacePos, 1, 1));
//
//	// ���[���h��ԍ��W�ƃJ�����ʒu���烌�C�𐶐�
//	worldPos.xyz /= worldPos.w;
//	float3 origin = cameraBuffer.position.xyz;
//	float3 direction = normalize(worldPos.xyz - origin);
//
//	RayDesc ray;
//	ray.Origin = origin;
//	ray.Direction = direction;
//
//	ray.TMin = 0;
//	ray.TMax = 10000;
//
//	Payload payload;
//	payload.color = float4(0, 0, 0, 1);
//	payload.traceCount = 1;
//	TraceRay(scene, 0, 0xff, 0, 2, 0, ray, payload);
//
//	outputTexture[index.xy] = payload.color;
//}
//
//[shader("miss")]
//void MissShader(inout Payload payload)
//{
//	payload.color = float4(0.5f, 0., 0.5, 1);
//}
//
//// ���˃x�N�g��
//float3 Reflect(float3 normal, float3 direction)
//{
//	return dot(normal, direction) * 2.0f * normal + direction;
//}
//
//float3 Lighting(Payload payload, float3 position, float3 normal, float3 view)
//{
//	float3 color = float3(0.0f, 0.0f, 0.0f);
//	color.rgb += (float3)payload.color.rgb * materialBuffer.ambientCoeff;
//
//	for (uint i = 0; i < sceneBuffer.lightCount; ++i)
//	{
//		LightData light = lightBuffer.Load(i);
//		float3 lightDirection = normalize(light.position - position;);
//
//		// Diffuse(�g�U����)�v�Z
//		float d = saturate(dot(lightDirection, normal));
//		float luminous = 0.5f;
//		float3 ref = (light.color * luminous * materialBuffer.diffuseCoeff) * d;
//
//		color.rgb += ref;
//
//		// Specular(���ʔ���)�v�Z
//		float c = dot(Reflect(normal, -lightDirection), view);
//		//float3 spe = materialBuffer.specularCoeff * pow(c, materialBuffer.specularity);
//		float3 spe = materialBuffer.specularCoeff * pow(c, 3);
//
//		color.rgb += spe;
//	}
//
//	return color;
//}
//
//// ���b�V���̃V�F�[�_�[(�������O���v�������΂Ȃ��������߂��̖��O)
//[shader("closesthit")]
//void MeshShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
//{
//	uint3 indices = Get32bitIndices(PrimitiveIndex());
//
//	float2 uvs[3] = {
//		uvBuffer[indices.x],
//		uvBuffer[indices.y],
//		uvBuffer[indices.z]
//	};
//
//	float2 uv = uvs[0] +
//		attribute.barycentrics.x * (uvs[1] - uvs[0]) +
//		attribute.barycentrics.y * (uvs[2] - uvs[0]);
//	float3 normal = normalBuffer[indices.x] +
//		attribute.barycentrics.x * (normalBuffer[indices.y] - normalBuffer[indices.x]) +
//		attribute.barycentrics.y * (normalBuffer[indices.z] - normalBuffer[indices.x]);
//
//	normal = normalize(normal);
//
//	float4 color = float4(1, 1, 1, 1);
//	color = tex.SampleLevel(sam, uv, 0);
//
//	float t = RayTCurrent();
//	float3 rayDirection = WorldRayDirection();
//	float3 rayOrigin = WorldRayOrigin();
//
//	float3 position = rayOrigin + t * rayDirection;
//	float3 offset = normal * 0.05f;
//	float3 lightDirection = GetPointLightDirection(position + offset);
//	RayDesc ray;
//	ray.Origin = position + offset;
//	ray.Direction = lightDirection;
//
//	ray.TMin = 0.01f;
//	ray.TMax = length(sceneBuffer.lightPosition - position);
//
//	ShadowPayload shadowPayload;
//	shadowPayload.shadowCoeff = 1.0f;
//
//	TraceRay(scene, 0, ~0b00000001, 1, 2, 1, ray, shadowPayload);
//	float shadow = shadowPayload.shadowCoeff;
//	
//	color.rgb += Lighting(payload, position, normal, rayDirection);
//	color.rgb *= shadow;
//
//	payload.color = color;
//}
//
//[shader("closesthit")]
//void SkyDomeShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
//{
//	uint3 indices = Get32bitIndices(PrimitiveIndex());
//
//	float2 uvs[3] = {
//		uvBuffer[indices.x],
//		uvBuffer[indices.y],
//		uvBuffer[indices.z]
//	};
//
//	float2 uv = uvs[0] +
//		attribute.barycentrics.x * (uvs[1] - uvs[0]) +
//		attribute.barycentrics.y * (uvs[2] - uvs[0]);
//
//	float3 normal = normalBuffer[indices.x] +
//		attribute.barycentrics.x * (normalBuffer[indices.y] - normalBuffer[indices.x]) +
//		attribute.barycentrics.y * (normalBuffer[indices.z] - normalBuffer[indices.x]);
//	normal = normalize(normal);
//
//	float4 color = float4(1, 1, 1, 1);
//	color = tex.SampleLevel(sam, uv, 0);
//
//	payload.color = color;
//}
//
//[shader("anyhit")]
//void AlphaCheckShader(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
//{
//	uint3 indices = Get32bitIndices(PrimitiveIndex());
//
//	float2 uvs[3] = {
//		uvBuffer[indices.x],
//		uvBuffer[indices.y],
//		uvBuffer[indices.z]
//	};
//
//	float2 uv = uvs[0] +
//		attribute.barycentrics.x * (uvs[1] - uvs[0]) +
//		attribute.barycentrics.y * (uvs[2] - uvs[0]);
//
//	float alpha = tex.SampleLevel(sam, uv, 0.0).a;
//	if (alpha < 0.01f)
//	{
//		IgnoreHit();
//	}
//
//}
//
//[shader("closesthit")]
//void ShadowHitShader(inout ShadowPayload payload, BuiltInTriangleIntersectionAttributes attribute)
//{
//	// �����������قǉe�𔖂�����K�v������
//	float t = RayTCurrent();
//	float s = 0.5f;
//	float r = clamp((t*t) * 4.0f / 10000.0f, 0.1f, 0.9f);
//	payload.shadowCoeff = 1.0f - s + r * s;
//}
//
//[shader("miss")]
//void ShadowMissShader(inout ShadowPayload payload)
//{
//	// �e���ł���@���@RGB�̒l������
//	// ������Ȃ���������
//	payload.shadowCoeff = 1.0f;
//}
//
//// ���ˏ����V�F�[�_�[
//[shader("closesthit")]
//void ReflectionShader(inout Payload payload, in SphereAttribute attribute)
//{
//	float3 rayDirection = WorldRayDirection();
//	float3 position = WorldRayOrigin() + WorldRayDirection() * RayTCurrent();
//	float3 normal = attribute.normal;
//	float3 reflection = dot(normal, -WorldRayDirection()) * 2.0 * normal + WorldRayDirection();
//	RayDesc ray;
//	ray.Origin = position + normal * 0.01f;
//
//	float4 color = (float4(materialBuffer.color, 1) * materialBuffer.opacity);
//	if (payload.traceCount < 3)
//	{
//		payload.traceCount++;
//		ray.Direction = reflection;
//		ray.TMin = 0.01;
//		ray.TMax = 2000;
//		Payload payload2;
//		payload2.color = float4(1, 1, 1, 1);
//		payload2.traceCount = 1;
//		TraceRay(scene, 0, 0xff, 0, 2, 0, ray, payload);
//
//		color += (payload.color * (1 - materialBuffer.opacity));
//	}
//	float3 lightDirection = GetPointLightDirection(position + normal * 0.01f);
//	ray.Direction = lightDirection;
//	ray.TMin = 0.001f;
//	ray.TMax = length(sceneBuffer.lightPosition - position);
//
//	ShadowPayload shadowPayload;
//	shadowPayload.shadowCoeff = 1.0f;
//
//	TraceRay(scene, 0, ~0b00000001, 1, 2, 1, ray, shadowPayload);
//	float shadow = shadowPayload.shadowCoeff;
//
//	color.rgb += Lighting(payload, position, normal, rayDirection);
//
//	payload.color = color * shadow;
//}
//
//float3 Refract(float3 normal, float3 incident, float refraction1, float refraction2)
//{
//	return float3(0, 0, 0);
//}
//
//// ���܏����V�F�[�_�[
//[shader("closesthit")]
//void RefractionShader(inout Payload payload, in SphereAttribute attribute)
//{
//	// https://knzw.tech/raytracing/?page_id=478
//
//	float n1 = 1.0;
//	float n2 = 1.0;
//	const float3 i = normalize(WorldRayDirection());
//	const float3 n = normalize(attribute.normal);
//	const float opacity = materialBuffer.opacity;
//	float4 color = float4(materialBuffer.color * opacity, opacity);
//
//	RayDesc ray;
//	if (payload.traceCount < 3)
//	{
//		// �O�������������O���Ŕ��ˌW���̓�������ς��
//		if (attribute.front)
//		{
//			n1 = sceneBuffer.refraction;
//			n2 = materialBuffer.refraction;
//		}
//		else
//		{
//			n1 = materialBuffer.refraction;
//			n2 = sceneBuffer.refraction;
//
//		}
//
//		// �X�l���̖@��
//		// ���K����̈ג����Ŋ���Ȃ��Ă���
//		const float cos1 = dot(i, n);
//
//		const float3 f = (n1 / n2) * (i - (sqrt((n2 / n1) * (n2 / n1)) - (1 - (cos1 * cos1)) - cos1) * n);
//
//		ray.Origin = attribute.position;
//		ray.Direction = f;
//		ray.TMin = 0.1;
//		ray.TMax = 10000;
//		//Payload payload2;
//		//payload2.color = float4(1, 1, 1, 1);
//		//payload2.traceCount = 1;
//
//		payload.traceCount++;
//		TraceRay(scene, 0, 0xff, 0, 2, 0, ray, payload);
//		color.rgb += payload.color.rgb * (1 - opacity);
//	}
//	float3 lightDirection = GetPointLightDirection(attribute.position + n * 0.01f);
//
//	ray.Origin = attribute.position + n * 0.01f;
//	ray.Direction = lightDirection;
//
//	ray.TMin = 0.001f;
//	ray.TMax = length(sceneBuffer.lightPosition - attribute.position);
//	ShadowPayload shadowPayload;
//	shadowPayload.shadowCoeff = 1.0f;
//
//	TraceRay(scene, 0, ~0b00000001, 1, 2, 1, ray, shadowPayload);
//	float shadow = shadowPayload.shadowCoeff;
//
//	float3 rayDirection = WorldRayDirection();
//	color.rgb += Lighting(payload, attribute.position, n, rayDirection);
//
//	payload.color = color * shadow;
//}
//
//void Swap(inout float a, inout float b)
//{
//	float tmp = a;
//	a = b;
//	b = tmp;
//}
//
//bool SphereIsHit(in Sphere sphere, in Ray ray, out float t1, out float t2)
//{
//	float3 l = ray.origin - sphere.center;
//	float a = dot(ray.direction, ray.direction);
//	float b = 2 * dot(l, ray.direction);
//	float c = dot(l, l) - (sphere.radius * sphere.radius);
//
//	// ���ʎ�
//	float d = (b * b) - (4 * a * c);
//
//	if (d < 0)
//	{
//		return false;
//	}
//	else if (d == 0)
//	{
//		float sd = sqrt(d);
//		t1 = (-b - sd) / (2 * a);
//		t2 = -1.0f;
//	}
//	else
//	{
//		float sd = sqrt(d);
//		t1 = (-b - sd) / (2 * a);
//		t2 = (-b + sd) / (2 * a);
//		// t1�̂ق����������Ȃ����
//		if (t1 > t2)
//		{
//			Swap(t1, t2);
//		}
//	}
//
//	return true;
//}
//
//
//// ���̃V�F�[�_�[�ɓ����Ă���Ƃ��̓��C�Ɖ�������̃C���X�^���X(AABB)�Ƀq�b�g������
//// �q�b�g�����Ƃ��ɂ���AABB�łǂ̂悤�Ȍ`��Ɠ������������v�Z���ŕ\�����邱�Ƃ��ł���
//[shader("intersection")]
//void SphereIntersectShader()
//{
//	// �g�ݍ��݊֐�
//	float3 rayOrigin = WorldRayOrigin();		// ���C�̊J�n�ʒu�擾
//	float3 rayDirection = WorldRayDirection();	// ���C�̌����x�N�g���擾
//	float rayTMin = RayTMin();
//	float t = 0.0f;								// ���C�̎����擾�A�����݂����Ȃ���
//
//	// ���[���h�ϊ���̍��W
//	float3x4 objectMatrix = ObjectToWorld3x4();
//	ProceduralInstance instance = proceduralBuffer.Load(0);
//	float3 minLocalPosition = instance.min;
//	float3 maxLocalPosition = instance.max;
//
//	float3 minWorldPosition = mul(objectMatrix, float4(minLocalPosition, 1));
//	float3 maxWorldPosition = mul(objectMatrix, float4(maxLocalPosition, 1));
//
//	Sphere sphere;
//	sphere.center.x = (maxWorldPosition.x + minWorldPosition.x) / 2;
//	sphere.center.y = (maxWorldPosition.y + minWorldPosition.y) / 2;
//	sphere.center.z = (maxWorldPosition.z + minWorldPosition.z) / 2;
//
//	sphere.radius = abs((maxWorldPosition.x - minWorldPosition.x) / 2);
//
//	Ray ray;
//	ray.origin = rayOrigin;
//	ray.direction = rayDirection;
//	float t1, t2;
//	if (SphereIsHit(sphere, ray, t1, t2))
//	{
//		if (t1 > rayTMin)
//		{
//			// �@�������߂�
//			// ���������ʒu���璆�S���W�������Ƌ��܂�
//			float3 hitPos = rayOrigin + (rayDirection * t1);
//
//			float3 normal = normalize(hitPos - sphere.center);
//
//			SphereAttribute attribute;
//
//			float b = dot(rayDirection, normal);
//			bool front = true;
//			if (b < 0)
//			{
//				normal = -normal;
//				front = false;
//			}
//
//			attribute.normal = normal;
//			attribute.position = hitPos;
//			attribute.front = front;
//			ReportHit(t1, 0, attribute);
//		}
//		else
//		{
//		}
//
//	}
//
//}

/*
Intersectoin�ŃA�j���[�V�����ł��邩��
���C�g���̃A�j���[�V�����̎�ނ͓����Ǝv��
instanceBuffer��Matrix��Ǐ]����{�[���̍s����g�p���Ă����@
���̂����͒Ǐ]����{�[���̐ݒ�̓T�u���b�V�����Ƃ̂��ߖ�肪�N���邩������Ȃ�
��ڂ�
intersectoin�֐����Œ��_���ړ������Ɖ��肵�ĎO�p�`�ƃ��C�̓����蔻����s��
*/

// AnyHitShader�ɂȂ�̂��ȁH�H�H�H
// �r���Ń��C�̕�����ς���ꂽ�炩�Ȃ�������ȁ`
// ���܏����V�F�[�_�[
//[shader("closesthit")]
//void RefractionShader(inout Payload payload, in  BuiltInTriangleIntersectionAttributes attribute)
//{
//	
//}


/*
DispatchRaysDimensions
DispatchRayDesc�̕��A�����A�[�x
���Ԃ��Ă���
*/

/*
����
�萔�o�b�t�@�͎g�p���閈�ɕύX�������
StructuredBuffer��
��ʂ̃f�[�^����ꕔ�A�N�Z�X����Ƃ��ɂ͂������߂̂���
*/
