#include "../hooks.h"

bool __fastcall createMove::hkCreateMove(void* ecx, void* udx, float frameTime, CUserCmd* command)
{
	if (!command)
		return false;

	global::localPlayer = gInterfaces.entList->GetClientEntity(gInterfaces.engine->getLocalPlayerIndex());

	if (global::localPlayer && global::localPlayer->isAlive())
	{
		bhop::CreateMove(command);
		radarhack::CreateMove();
	}
	return false;
}
