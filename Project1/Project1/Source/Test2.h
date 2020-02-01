#pragma once
#include <Windows.h>
#include <DirectXMath.h>

static DirectX::XMFLOAT3 s_LightPosition = DirectX::XMFLOAT3(50.0f, 50.0f, -50.0f);

class Test2
{
private:

public:
	void Init(HWND hWnd);

	void Update(float deltaTime);

	void Render();

	void Fin();
};
