#include "../features.h"

void novisualrecoil::run()
{
	if (!vars::misc::removalsSelect[1])
		return;
	vec3_t zeroAngle = { 0,0,0 };

	auto &recoilPunch = global::localPlayer->getRecoilPunchAngle();
	auto &recoilViewPunch = global::localPlayer->getRecoilViewPunchAngle();

	recoilPunch = zeroAngle;
	recoilViewPunch = zeroAngle;
}
