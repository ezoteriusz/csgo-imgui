#pragma once

class IDebugOverlay {
public:
	virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ...) = 0;
};