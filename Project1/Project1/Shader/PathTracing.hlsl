#include "RaytracingStruct.hlsli"

RWTexture2D<float4> outputTexture : register(u0);

RaytracingAccelerationStructure	scene : register(t0, space0);

ConstantBuffer<SceneData> sceneBuffer : register(b0);

[shader("raygeneration")]
void RayGenerate()
{
}

//[shader("closesthit")]
//void Hit()
//{
//
//}

//[shader("miss")]
//void Miss()
//{
//
//}