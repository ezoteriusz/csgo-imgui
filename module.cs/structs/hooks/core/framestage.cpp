#include "../hooks.h"

void __fastcall framestage::hkFrameStage(void* ecx, void* udx, ClientFrameStageT id)
{
	global::localPlayer = gInterfaces.entList->GetClientEntity(gInterfaces.engine->getLocalPlayerIndex());
	if (!global::localPlayer)
		return;
	switch (id)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		noflash::FrameStageNotify();
		novisualrecoil::run();
		break;
	}
	oFrameStage(ecx, udx, id);
}
