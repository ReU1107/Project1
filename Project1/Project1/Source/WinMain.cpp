#include <windows.h>
#include <cstdint>
#include <wrl/wrappers/corewrappers.h>
#include <locale.h>
//#include <cassert>
//#include <wrl/client.h>
#include <thread>
#include "Test4.h"
#include "Resolution.h"
#include "Engine/Utility/Timer.h"

HWND hWnd;

using namespace Engine;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassNme[] = "ウィンドウクラス・ネーム";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
	unsigned int a = 0x3f170a3d;
	float b = *(float*)&a;
	unsigned int c = 0x3ed1eb86;
	float d = *(float*)&c;
	setlocale(LC_ALL, "");


	MSG msg;
	WNDCLASS myProg;
	if (!hPreInst) 
	{
		myProg.style = CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc = WndProc;
		myProg.cbClsExtra = 0;
		myProg.cbWndExtra = 0;
		myProg.hInstance = hInstance;
		myProg.hIcon = NULL;
		myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		myProg.lpszMenuName = NULL;
		myProg.lpszClassName = szClassNme;
		if (!RegisterClass(&myProg))
			return FALSE;
	}

	RECT rect = {};
	rect.left = 0;
	rect.right = ResolutionWidth;
	rect.top = 0;
	rect.bottom = ResolutionHeight;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SIZE windowSize;
	windowSize.cx = rect.right - rect.left;
	windowSize.cy = rect.bottom - rect.top;

	hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		szClassNme,
		"DirectX Raytracing",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowSize.cx,
		windowSize.cy,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#if 0
#else

	Test4 test;
#endif	
	test.Init(hWnd);

	float deltaTime = 1.0f / 60.0f;

	static uint32_t frameCount = 0;

	Timer fpsTimer;
	fpsTimer.Start();
	std::chrono::milliseconds fpsChrono = std::chrono::milliseconds(16);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// FPS抑制
			// 経過時間が1フレームの時間を過ぎたなら更新
			std::chrono::milliseconds elapsedTime = Timer::s_globalClock.GetElapsedTime();
			if (elapsedTime >= fpsChrono)
			{

				test.Update(deltaTime);
				test.Render();
				frameCount++;

				// 1秒(1000ミリ秒)経ったらFPS更新
				if (fpsTimer.GetElapsedTime() >= std::chrono::milliseconds(1000))
				{

					auto a = fpsTimer.GetElapsedTime().count();
					const float fps = (float)((frameCount * 1000) / (float)fpsTimer.GetElapsedTime().count());

					// fpsを基にゲームスピード変更
					deltaTime = 1.0f / fps;

					char text[256];
					sprintf_s(text, "fps = %6.4f", fps);
					SetWindowText(hWnd, text);
					fpsTimer.Reset();
					frameCount = 0;
				}
				// 経過時間リセット
				Timer::s_globalClock.Reset();
			}
			else 
			{
				// フレームの時間を過ぎるまで眠らせる
				std::this_thread::sleep_for(std::chrono::milliseconds(elapsedTime - fpsChrono));
			}
		}
	}
	test.Fin();

	return (int)(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		uint32_t count = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
		for (uint32_t i = 0; i < count; ++i)
		{
			char filePath[512];
			DragQueryFile(hDrop, i, filePath, 512);
			int a = 0;
		}
	}	break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}