#include "../hooks.h"
#include "../../../gui/menu/menu.h"

long __stdcall presentscene::wnd_proc(HWND window, UINT msg, WPARAM wparm, LPARAM lparm)
{
	[[maybe_unused]] static const auto once = [](const HWND& window) noexcept
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(window);

		return true;
	}(window);

	long ImGui_ImplWin32_WndProcHandler(HWND window, UINT msg, WPARAM wparm, LPARAM lparm);
	ImGui_ImplWin32_WndProcHandler(window, msg, wparm, lparm);
	return CallWindowProcA(wnd_procOrginal, window, msg, wparm, lparm);
}

long __stdcall presentscene::hkResetScene(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	return resetOriginal(device, params);
}

long __stdcall presentscene::hkPresentScene(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND window_override, const RGNDATA* dirty_region)
{
	if (!ImGui::GetCurrentContext()) return presentOriginal(device, src, dest, window_override, dirty_region);

	static const bool imgui_init{ ImGui_ImplDX9_Init(device) };
	static const bool menu_init{ menu::initialize() };

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::IsKeyPressed(VK_INSERT, false))
	{
		menu::is_open = !menu::is_open;
	}

	menu::render();

	ImGui::EndFrame();
	ImGui::Render();

	if (device->BeginScene() == D3D_OK)
	{
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}
	return presentOriginal(device, src, dest, window_override, dirty_region);
}
