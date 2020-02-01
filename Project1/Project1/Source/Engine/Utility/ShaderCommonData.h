#pragma once

#ifdef __cplusplus
#include "../Math/Include.h"
#include <cstdint>

using float2 = Engine::Vector2;
using float3 = Engine::Vector3;
using float4 = Engine::Vector4;
using matrix = Engine::Matrix4x4;
using float4x4 = Engine::Matrix4x4;
using uint = uint32_t;

#endif

#ifdef __cplusplus
#define SEMANTIC(sem) 
#else
#define SEMANTIC(sem) : sem
#endif