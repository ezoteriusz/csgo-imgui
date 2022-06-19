#include "../features.h"

static void clantagchanger::run(const char* tag, const char* name)
{
	static auto set_clantag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(gUtils.PatternScan("engine.dll", "53 56 57 8B DA 8B F9 FF 15"));
	set_clantag(tag, name);
}