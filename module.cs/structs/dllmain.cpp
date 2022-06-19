#include "utils.h"
#include "../interfaces/interfaces.h"
#include "netvar/netvar.h"
#include "hooks/hooks.h"
#include "../gui/renderer/renderer.h"
unsigned long startAddress(HMODULE hModule)
{
	gUtils.sysConsole.attach();
	gUtils.sysConsole.setcolor(9);
	std::cout << "[BUILD] Info: DEBUG | DATE: " << __TIMESTAMP__ << "\n";
	gInterfaces.init();
	gNetvars.Setup();
	render::initialize();
	gHooks.init();
	
	while (!GetAsyncKeyState(VK_DELETE))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	gHooks.detach();
	gUtils.sysConsole.detach();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD sReason, LPVOID lpReserved)
{
	switch (sReason)
	{
	case DLL_PROCESS_ATTACH:
		auto pThread = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(startAddress), hModule, 0, nullptr);
		if (pThread)
			CloseHandle(pThread);
		break;
	}
	return TRUE;
}