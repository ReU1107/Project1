#pragma once

#include "GraphicsSystem/Include.h"

#include "ThreadSystem/Include.h"

#include "GUISystem/Include.h"

#include "Math/Include.h"

#include "String/Include.h"

#include "Utility/Include.h"

#include "GameObject/Include.h"

#include "SceneManagement/Include.h"

#include "AnimationSystem/Include.h"

#include "AudioSystem/Include.h"

#include "PhysicsSystem/Include.h"

void DebugString(const char* filePath, int lineNumber, const char* funcName, const char* format, ...);

#define DBGSTR(format,...) DebugString(__FILE__,__LINE__,__func__,format,__VA_ARGS__)