#include "../features.h"

void radarhack::CreateMove()
{
	if (!vars::misc::radarhack)
		return;
	for (int i = 0; i <= gInterfaces.engine->getMaxClients(); i++)
	{
		auto entity = gInterfaces.entList->GetClientEntity(i);
		if (!entity)
			continue;
		entity->setEntitySpotted() = true;
	}
}
