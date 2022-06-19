#include "../features.h"

bool get_playerbox(CEntity* ent, box& in)
{
	vec2_t flb, brt, blb, frt, frb, brb, blt, flt;

	const auto &origin = ent->absOrigin();
	const auto min = ent->collideable()->mins() + origin;
	const auto max = ent->collideable()->maxs() + origin;

	vec3_t points[] = {
		vec3_t(min.x, min.y, min.z),
		vec3_t(min.x, max.y, min.z),
		vec3_t(max.x, max.y, min.z),
		vec3_t(max.x, min.y, min.z),
		vec3_t(max.x, max.y, max.z),
		vec3_t(min.x, max.y, max.z),
		vec3_t(min.x, min.y, max.z),
		vec3_t(max.x, min.y, max.z)
	};

	if (!math::world_to_screen(points[3], flb) || !math::world_to_screen(points[5], brt)
		|| !math::world_to_screen(points[0], blb) || !math::world_to_screen(points[4], frt)
		|| !math::world_to_screen(points[2], frb) || !math::world_to_screen(points[1], brb)
		|| !math::world_to_screen(points[6], blt) || !math::world_to_screen(points[7], flt))
		return false;

	vec2_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 1; i < 8; ++i)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	in.x = static_cast<int>(left);
	in.y = static_cast<int>(top);
	in.w = static_cast<int>(right - left);
	in.h = static_cast<int>(bottom - top);

	return true;
}

const color history{ 255, 255, 255,150 };
const color history_outline{ 0,0,0,60 };

void PlayerEsp::render()
{
	for (int i = 1; i <= gInterfaces.engine->getMaxClients(); ++i)
	{
		auto* const entity = static_cast<CEntity*>(gInterfaces.entList->GetClientEntity(i));
		if (!entity || !global::localPlayer || entity == global::localPlayer || entity->getEntityHealth() <= 0 /*|| entity->dormant()*/) continue;
		if (entity->getEntityTeam() == global::localPlayer->getEntityTeam()) continue;
		gInterfaces.engine->GetPlayerInfo(i, &entInfo);
		esp(entity);
	}
}

void PlayerEsp::esp(CEntity* entity)
{
	box bbox;
	if(!get_playerbox(entity, bbox)) return;
	if (!vars::esp::playerEsp)
		return;

	if (vars::esp::box)
	{
		render::draw_outline(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, entity->isDormant() ? history_outline : color(1, 1, 1, 255));
		render::draw_rect(bbox.x, bbox.y, bbox.w, bbox.h, entity->isDormant() ? history :  color(255, 255, 255));
		render::draw_outline(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, entity->isDormant() ? history_outline : color(1, 1, 1, 255));
	}
	if (vars::esp::name)
	{
		std::string print(entInfo.fakeplayer ? std::string("[BOT] ").append(entInfo.name).c_str() : entInfo.name);
		//std::transform(print.begin(), print.end(), print.begin(), ::tolower);

		std::string name_lower = entInfo.name;
		std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);
		render::text(bbox.x + (bbox.w / 2), bbox.y - 13, render::fonts::esp_flags, print, true,entity->isDormant() ? history : color(255,255,255,255));
	}

	if (vars::esp::flags)
	{
		std::string Money = std::to_string(entity->getEntityMoney());
		std::string Flashed = std::to_string(entity->isFlashed());
		std::string IsScoped = std::to_string(entity->isScoped());

		int MoneyH = render::get_text_size(render::fonts::esp_flags, "$" + Money).y;
		int FlashedH = render::get_text_size(render::fonts::esp_flags, Flashed).y;
		int ScopedH = render::get_text_size(render::fonts::esp_flags, IsScoped).y;

		if (entity->isFlashed())
		{
			Flashed = "*blind*";
		}
		else {
			Flashed = "";
			FlashedH = 0;
		}

		if (entity->isScoped())
		{
			IsScoped = "*zoom*";
		}
		else {
			ScopedH = 0;
			IsScoped = "";
		}

		if (vars::esp::flagsSelect[2])
		{
			render::text(bbox.x + bbox.w + 5, bbox.y + 2, render::fonts::esp_flags, "$" + Money, false, color(77, 219, 115));
		}
		if (vars::esp::flagsSelect[1])
		{
			render::text(bbox.x + bbox.w + 5, bbox.y + 2 + MoneyH + 1, render::fonts::esp_flags, IsScoped, false, color(110, 153, 230));
		}
		if (vars::esp::flagsSelect[0])
		{
			render::text(bbox.x + bbox.w + 5, bbox.y + 2 + ScopedH + 1 + +MoneyH + 1, render::fonts::esp_flags, Flashed, false, color(110, 153, 230));
		}
	}


	if (vars::esp::healthbar)
	{
		auto health_color = color((255 - entity->getEntityHealth() * 2.55), (entity->getEntityHealth() * 2.55), 0, 255);
		std::string healthStr = std::to_string(entity->getEntityHealth());
		box temp2(bbox.x - 5, bbox.y + (bbox.h - bbox.h * (std::clamp<int>(entity->getEntityHealth(), 0, 100.f) / 100.f)), 1, bbox.h * (std::clamp<int>(entity->getEntityHealth(), 0, 100) / 100.f) - (entity->getEntityHealth() >= 100 ? 0 : -1));
		box temp_bg2(bbox.x - 5, bbox.y, 1, bbox.h);
		render::draw_filled_rect(temp_bg2.x - 1, temp_bg2.y - 1, temp_bg2.w + 2, temp_bg2.h + 2, entity->isDormant() ? history_outline : color(0, 0, 0, 255));
		render::draw_filled_rect(temp2.x, temp2.y, temp2.w, temp2.h, entity->isDormant() ? history_outline : color(health_color));
		if (!vars::esp::showtext)
			return;
		if (entity->getEntityHealth() < 100)
		{
			render::text(temp2.x - 7, temp2.y - 2, render::fonts::watermark_font, healthStr, true, entity->isDormant() ? history : color(health_color));
		}
	}



}