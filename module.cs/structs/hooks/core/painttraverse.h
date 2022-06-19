#pragma once

namespace paintTraverse {
	using paintTraverseFn = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
	inline paintTraverseFn oPaintTraverse = nullptr;
	void __stdcall hkPaintTraverseHook(unsigned int panel, bool force_repaint, bool allow_force);
}