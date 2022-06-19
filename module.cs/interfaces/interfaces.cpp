#include "interfaces.h"
CInterfaces gInterfaces;
bool CInterfaces::init()
{
	client = reinterpret_cast<IClient*>(getInterface("client.dll", "VClient018"));
	entList = reinterpret_cast<IClientEntityList*>(getInterface("client.dll", "VClientEntityList003"));
	engine = reinterpret_cast<IClientEngine*>(getInterface("engine.dll", "VEngineClient014"));
	debugOverlay = reinterpret_cast<IDebugOverlay*>(getInterface("engine.dll", "VDebugOverlay004"));
	surface = reinterpret_cast<ISurface*>(getInterface("vguimatsurface.dll", "VGUI_Surface031"));
	panel = reinterpret_cast<IPanel*>(getInterface("vgui2.dll", "VGUI_Panel009"));

	glowManager = reinterpret_cast<IGlowManager*>(*reinterpret_cast<uintptr_t*>(gUtils.PatternScan("client.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 3));
	directx9 = **(IDirect3DDevice9***)(gUtils.PatternScan("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	clientMode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
	

	std::cout << "[INFO] Interfaces loaded correctly\n";
	return true;
}

void* CInterfaces::getInterface(const char* mod, const char* iface) {
	using fn_capture_iface_t = void* (*)(const char*, int*);
	auto fn_addr = (fn_capture_iface_t)GetProcAddress(GetModuleHandleA(mod), "CreateInterface");

	auto iface_addr = fn_addr(iface, nullptr);

	printf("[LOG] interface %s located at 0x%p\n", iface, fn_addr(iface, nullptr));
	return iface_addr;
}