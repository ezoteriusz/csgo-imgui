#include "../features.h"
bool var;
void noflash::FrameStageNotify()
{
	if (!vars::misc::removalsSelect[0])
		return;

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		var = !var;
	}
	global::localPlayer->getEntityFlashMaxAlpha() = var ? 0.f : 255.f;
}
