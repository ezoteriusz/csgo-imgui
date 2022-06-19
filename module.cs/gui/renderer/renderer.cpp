#include "renderer.h"

unsigned long render::fonts::watermark_font;

void render::initialize() {
	render::fonts::watermark_font = gInterfaces.surface->font_create();

	gInterfaces.surface->set_font_glyph(render::fonts::watermark_font, "Consolas", 12, 500, 0, 0, font_flags::fontflag_outline);

	std::cout<<"[LOG] Render Initialized!\n";
}

void render::draw_line(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, color colour) {
	gInterfaces.surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
	gInterfaces.surface->draw_line(x1, y1, x2, y2);
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color) {
	gInterfaces.surface->draw_text_font(font);
	int text_width, text_height;

	if (centered) {
		gInterfaces.surface->get_text_size(font, text, text_width, text_height);
		gInterfaces.surface->draw_text_pos(x - text_width / 2, y);
	}
	else
		gInterfaces.surface->draw_text_pos(x, y);

	gInterfaces.surface->set_text_color(color.r, color.g, color.b, color.a);
	gInterfaces.surface->draw_render_text(text, wcslen(text));
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color) {
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		gInterfaces.surface->draw_text_font(font);
		if (centered) {
			gInterfaces.surface->get_text_size(font, temp, text_width, text_height);
			gInterfaces.surface->draw_text_pos(x - text_width / 2, y);
		}
		else
			gInterfaces.surface->draw_text_pos(x, y);
		gInterfaces.surface->set_text_color(color.r, color.g, color.b, color.a);
		gInterfaces.surface->draw_render_text(temp, wcslen(temp));
	}
}

void render::draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	gInterfaces.surface->set_drawing_color(color.r, color.g, color.b, color.a);
	gInterfaces.surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	gInterfaces.surface->set_drawing_color(color.r, color.g, color.b, color.a);
	gInterfaces.surface->draw_filled_rectangle(x, y, width, height);
}

void render::draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	gInterfaces.surface->set_drawing_color(color.r, color.g, color.b, color.a);
	gInterfaces.surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_textured_polygon(std::int32_t vertices_count, vertex_t* vertices, color color) {
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	unsigned int texture_id{};
	if (!texture_id) {
		texture_id = gInterfaces.surface->create_new_texture_id(true);
		gInterfaces.surface->set_texture_rgba(texture_id, buf, 1, 1);
	}
	gInterfaces.surface->set_drawing_color(color.r, color.g, color.b, color.a);
	gInterfaces.surface->set_texture(texture_id);
	gInterfaces.surface->draw_polygon(vertices_count, vertices);
}

void render::draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color) {
	float step = M_PI * 2.0 / segments;
	for (float a = 0; a < (M_PI * 2.0); a += step) {
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + step) + x;
		float y2 = radius * sin(a + step) + y;
		gInterfaces.surface->set_drawing_color(color.r, color.g, color.b, color.a);
		gInterfaces.surface->draw_line(x1, y1, x2, y2);
	}
}

vec2_t render::get_text_size(unsigned long font, std::string text) {
	std::wstring a(text.begin(), text.end());
	const wchar_t* wstr = a.c_str();
	static int w, h;

	gInterfaces.surface->get_text_size(font, wstr, w, h);
	return { static_cast<float>(w), static_cast<float>(h) };
}
