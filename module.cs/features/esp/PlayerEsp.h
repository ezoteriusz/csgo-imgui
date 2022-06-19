#pragma once
namespace PlayerEsp
{
	inline player_info_t entInfo;
	void render();
	void esp(CEntity * entity);
}

struct box
{
	int x, y, w, h;
	box() = default;
	box(const int x, const int y, const int w, const int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};