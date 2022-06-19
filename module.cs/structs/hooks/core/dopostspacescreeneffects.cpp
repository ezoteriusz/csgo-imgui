#include "../hooks.h"

void __stdcall dopostspacescreeneffects::hkDoPostSpaceScreenEffects(const void* viewSetup)
{
	CEntity* localPlayer = gInterfaces.entList->GetClientEntity(gInterfaces.engine->getLocalPlayerIndex());

	if (!vars::esp::playerEsp || !vars::esp::glow)
		return;

	if (localPlayer && gInterfaces.engine->isInGame())
	{
		for (int i = 0; i < gInterfaces.glowManager->glowObjects.size; ++i)
		{
			IGlowManager::CGlowObject& glowObject = gInterfaces.glowManager->glowObjects[i];
			if (glowObject.IsUnused())
				continue;
			if (!glowObject.entity)
				continue;

			switch (glowObject.entity->getEntityClass()->classID)
			{
			case CClientClass::CCSPlayer:
				if (!glowObject.entity->isAlive())
					break;
				if (glowObject.entity->getEntityTeam() != localPlayer->getEntityTeam())
				{
					glowObject.SetColor(vars::esp::glowRGB[0], vars::esp::glowRGB[1], vars::esp::glowRGB[2], 1.f);
				}
				break;
			default:
				break;
			}
		}
	}

	oDoPostSpaceScreenEffects(gInterfaces.clientMode, viewSetup);
}
