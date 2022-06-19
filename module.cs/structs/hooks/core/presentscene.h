#pragma once


namespace presentscene {
	long __stdcall wnd_proc(HWND window, UINT msg, WPARAM wparm, LPARAM lparm);
	long __stdcall hkResetScene(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
	long __stdcall hkPresentScene(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND window_override, const RGNDATA* dirty_region);
	inline WNDPROC wnd_procOrginal;
	inline std::add_pointer_t<long __stdcall(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> resetOriginal;
	inline std::add_pointer_t<long __stdcall(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> presentOriginal;
}