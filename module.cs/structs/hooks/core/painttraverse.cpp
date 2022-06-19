#include "../hooks.h"
#include "../../../gui/renderer/renderer.h"
#include "../../../features/esp/PlayerEsp.h"
#include "../../../gui/menu/menu.h"
void __stdcall paintTraverse::hkPaintTraverseHook(unsigned int panel, bool force_repaint, bool allow_force)
{
	auto panel_to_draw = fnv::hash(gInterfaces.panel->GetPanelName(panel));

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):

		render::text(10, 10, render::fonts::watermark_font, "build debug", false, color::white(255));
		PlayerEsp::render();
		//menu::toggle();
		//menu::render();
		break;

	case fnv::hash("FocusOverlayPanel"):
		//gInterfaces.panel->SetKeyboardInputEnabled(panel, menu::is_open);
		gInterfaces.panel->SetMouseInputEnabled(panel, menu::is_open);
		break;
	case fnv::hash("HudZoom"):
		if (!vars::misc::removalsSelect[2])
			return;
		int w, h;
		gInterfaces.engine->getScreenSize(w, h);
		
		if (global::localPlayer->isScoped()) {
			gInterfaces.surface->set_drawing_color(15, 15, 15, 255);
			gInterfaces.surface->draw_line(w / 2, 0, w / 2, h);
			gInterfaces.surface->draw_line(0, h / 2, w, h / 2);
		}
		return;
		break;
	}

	oPaintTraverse(gInterfaces.panel, panel, force_repaint, allow_force);
}
