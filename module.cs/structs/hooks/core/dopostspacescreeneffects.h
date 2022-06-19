#pragma once

namespace dopostspacescreeneffects {
	using org = void(__thiscall*)(IClientMode*, const void*);
	inline org oDoPostSpaceScreenEffects = nullptr;
	void __stdcall hkDoPostSpaceScreenEffects(const void* viewSetup);
}