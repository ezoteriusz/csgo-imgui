#include "../features.h"

void bhop::CreateMove(CUserCmd* command)
{
	if (!vars::misc::bhop)
		return;
	if (!(global::localPlayer->getEntityFlags() & CEntity::EFlags::FL_ONGROUND))
		command->buttons &= ~CUserCmd::IN_JUMP;
}
