#include "GUISystem.h"
#include "../../../Library/imgui/imgui.h"
#include <Windows.h>
#include <cstdint>
#include "../GraphicsSystem/Texture/Texture2D.h"

namespace Engine
{
	namespace GUISystem
	{
		static HWND s_hWnd = nullptr;
		static int64_t s_time = 0;
		static int64_t s_ticksPerSecond = 0;
		void Startup(void* hWnd)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			s_hWnd = (HWND)hWnd;

			ImGui::StyleColorsDark();
			ImGuiIO& io = ImGui::GetIO();
			io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
			io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
			io.BackendPlatformName = "";
			io.ImeWindowHandle = s_hWnd;
			
			unsigned char* pixels;
			int width, height;
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

			io.Fonts->Build();
			io.Fonts->AddFontDefault();
		}

		void W()
		{
			ImGuiIO& io = ImGui::GetIO();
			IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

			// Setup display size (every frame to accommodate for window resizing)
			RECT rect;
			::GetClientRect(s_hWnd, &rect);
			io.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));

			// Setup time step
			INT64 current_time;
			::QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
			io.DeltaTime = (float)(current_time - s_time) / s_ticksPerSecond;
			s_time = current_time;

			ImGui::NewFrame();
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
			ImGui::SetNextWindowPos(ImVec2(20, 20));
			ImGui::SetNextWindowSize(ImVec2(200, 300));

			ImGui::Begin("config 1");

			ImGui::End();

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		void Shutdown()
		{
			ImGui::DestroyContext();
		}
	}
}