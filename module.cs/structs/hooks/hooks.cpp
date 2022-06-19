#include "hooks.h"
CHooks gHooks;
bool CHooks::init()
{
	const auto createMoveTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.clientMode, 24));
	const auto doPostSpaceScreenEffectsTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.clientMode, 44));
	const auto frameStageTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.client, 37));
	const auto paintTraverseTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.panel, 41));
	const auto resetTargetTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.directx9, 16));
	const auto presentTargetTable = reinterpret_cast<void*>(getVirtualTable(gInterfaces.directx9, 17));

	presentscene::wnd_procOrginal = reinterpret_cast<decltype(presentscene::wnd_procOrginal)>(SetWindowLongA(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG>(presentscene::wnd_proc)));


	MH_Initialize();
	MH_CreateHook(createMoveTable, &createMove::hkCreateMove, reinterpret_cast<void**>(&createMove::oCreateMove));
	MH_CreateHook(doPostSpaceScreenEffectsTable, &dopostspacescreeneffects::hkDoPostSpaceScreenEffects, reinterpret_cast<void**>(&dopostspacescreeneffects::oDoPostSpaceScreenEffects));
	MH_CreateHook(frameStageTable, &framestage::hkFrameStage, reinterpret_cast<void**>(&framestage::oFrameStage));
	MH_CreateHook(paintTraverseTable, &paintTraverse::hkPaintTraverseHook, reinterpret_cast<void**>(&paintTraverse::oPaintTraverse));
	MH_CreateHook(resetTargetTable, &presentscene::hkResetScene, reinterpret_cast<void**>(&presentscene::resetOriginal));
	MH_CreateHook(presentTargetTable, &presentscene::hkPresentScene, reinterpret_cast<void**>(&presentscene::presentOriginal));
	MH_EnableHook(MH_ALL_HOOKS);

	return true;
}

void CHooks::detach()
{
	MH_Uninitialize();
	MH_RemoveHook(MH_ALL_HOOKS);
	if (presentscene::wnd_procOrginal)
	{
		SetWindowLongA(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG>(presentscene::wnd_procOrginal));
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();

	if (ImGui::GetCurrentContext())
	{
		ImGui::DestroyContext();
	}
}
